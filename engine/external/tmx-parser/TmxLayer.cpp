//-----------------------------------------------------------------------------
// TmxLayer.cpp
//
// Copyright (c) 2010-2012, Tamir Atias
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Tamir Atias
//-----------------------------------------------------------------------------
#include <ticpp/tinyxml.h>
#include <zlib-1.2.7/zlib.h>
#include <stdlib.h>
#include <stdio.h>

#include "TmxLayer.h"
#include "TmxUtil.h"
#include "TmxMap.h"
#include "TmxTileset.h"

namespace Tmx 
{
	Layer::Layer(const Map *_map) 
		: map(_map)
		, name() 
		, width(0) 
		, height(0) 
		, opacity(1.0f)
		, visible(true)
		, properties()
	{		
	}

	Layer::~Layer() 
	{
		
	}

	void Layer::ParseLayer(const TiXmlNode *layerNode) 
	{
		const TiXmlElement *layerElem = layerNode->ToElement();
	
		// Read the attributes.
		name = layerElem->Attribute("name");

		layerElem->Attribute("width", &width);
		layerElem->Attribute("height", &height);

		const char *opacityStr = layerElem->Attribute("opacity");
		if (opacityStr) 
		{
			opacity = (float)atof(opacityStr);
		}

		const char *visibleStr = layerElem->Attribute("visible");
		if (visibleStr) 
		{
			visible = atoi(visibleStr) != 0; // to prevent visual c++ from complaining..
		}

		// Read the properties.
		const TiXmlNode *propertiesNode = layerNode->FirstChild("properties");
		if (propertiesNode) 
		{
			properties.Parse(propertiesNode);
		}
	}

		
	TileLayer::TileLayer(const Map *_map) 
		: Layer(_map)
		, encoding(TMX_ENCODING_XML)
		, compression(TMX_COMPRESSION_NONE)
	{
		// Set the map to null to specify that it is not yet allocated.
		tile_map = NULL;
	}

	TileLayer::~TileLayer() 
	{
		// If the tile map is allocated, delete it from the memory.
		if (tile_map)
		{
			delete [] tile_map;
			tile_map = NULL;
		}
	}

	void TileLayer::Parse(const TiXmlNode *layerNode) 
	{
		ParseLayer(layerNode);
		// Allocate memory for reading the tiles.
		tile_map = new MapTile[GetWidth() * GetHeight()];

		const TiXmlNode *dataNode = layerNode->FirstChild("data");
		const TiXmlElement *dataElem = dataNode->ToElement();

		const char *encodingStr = dataElem->Attribute("encoding");
		const char *compressionStr = dataElem->Attribute("compression");

		// Check for encoding.
		if (encodingStr) 
		{
			if (!strcmp(encodingStr, "base64")) 
			{
				encoding = TMX_ENCODING_BASE64;
			} 
			else if (!strcmp(encodingStr, "csv")) 
			{
				encoding = TMX_ENCODING_CSV;
			}
		}

		// Check for compression.
		if (compressionStr) 
		{
			if (!strcmp(compressionStr, "gzip")) 
			{
				compression = TMX_COMPRESSION_GZIP;
			} 
			else if (!strcmp(compressionStr, "zlib")) 
			{
				compression = TMX_COMPRESSION_ZLIB;
			}
		}
		
		// Decode.
		switch (encoding) 
		{
		case TMX_ENCODING_XML:
			ParseXML(dataNode);
			break;

		case TMX_ENCODING_BASE64:
			ParseBase64(dataElem->GetText());
			break;

		case TMX_ENCODING_CSV:
			ParseCSV(dataElem->GetText());
			break;
		}
	}

	void TileLayer::ParseXML(const TiXmlNode *dataNode) 
	{
		const TiXmlNode *tileNode = dataNode->FirstChild("tile");
		size_t tileCount = 0;

		while (tileNode) 
		{
			const TiXmlElement *tileElem = tileNode->ToElement();
			
			unsigned gid = 0;

			// Read the Global-ID of the tile.
			const char* gidText = tileElem->Attribute("gid");

			// Convert to an unsigned.
			sscanf(gidText, "%u", &gid);

			// Find the tileset index.
			const int tilesetIndex = GetMap()->FindTilesetIndex(gid);
			if (tilesetIndex != -1)
			{
				// If valid, set up the map tile with the tileset.
				const Tmx::Tileset* tileset = GetMap()->GetTileset(tilesetIndex);
				tile_map[tileCount] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
			}
			else
			{
				// Otherwise, make it null.
				tile_map[tileCount] = MapTile(gid, 0, (unsigned int)-1);
			}

			tileNode = dataNode->IterateChildren("tile", tileNode);
			tileCount++;
		}
	}

	void TileLayer::ParseBase64(const std::string &innerText) 
	{
		const std::string &text = Util::DecodeBase64(innerText);

		// Temporary array of gids to be converted to map tiles.
		unsigned *out = 0;

		if (compression == TMX_COMPRESSION_ZLIB) 
		{
			// Use zlib to uncompress the layer into the temporary array of tiles.
			uLongf outlen = GetWidth() * GetHeight() * 4;
			out = (unsigned *)malloc(outlen);
			uncompress(
				(Bytef*)out, &outlen, 
				(const Bytef*)text.c_str(), text.size());
	
		} 
		else if (compression == TMX_COMPRESSION_GZIP) 
		{
			// Use the utility class for decompressing (which uses zlib)
			out = (unsigned *)Util::DecompressGZIP(
				text.c_str(), 
				text.size(), 
				GetWidth() * GetWidth() * 4);
		} 
		else 
		{
			out = (unsigned *)malloc(text.size());
		
			// Copy every gid into the temporary array since
			// the decoded string is an array of 32-bit integers.
			memcpy(out, text.c_str(), text.size());
		}

		// Convert the gids to map tiles.
		for (int x = 0; x < GetWidth(); x++)
		{
			for (int y = 0; y < GetHeight(); y++)
			{
				unsigned gid = out[y * GetWidth() + x];

				// Find the tileset index.
				const int tilesetIndex = GetMap()->FindTilesetIndex(gid);
				if (tilesetIndex != -1)
				{
					// If valid, set up the map tile with the tileset.
					const Tmx::Tileset* tileset = GetMap()->GetTileset(tilesetIndex);
					tile_map[y * GetWidth() + x] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
				}
				else
				{
					// Otherwise, make it null.
					tile_map[y * GetWidth() + x] = MapTile(gid, 0, (unsigned int)-1);
				}
			}
		}

		// Free the temporary array from memory.
		free(out);
	}

	inline char* strdup(const char* s)
	{
#if defined(WIN32)
		return _strdup(s);
#else
		return ::strdup(s);
#endif
	}

	void TileLayer::ParseCSV(const std::string &innerText) 
	{
		// Duplicate the string for use with C stdio.
		char *csv = strdup(innerText.c_str());
		
		// Iterate through every token of ';' in the CSV string.
		char *pch = strtok(csv, ",");
		size_t tileCount = 0;
		
		while (pch) 
		{
			unsigned gid;
			sscanf(pch, "%u", &gid);

			// Find the tileset index.
			const int tilesetIndex = GetMap()->FindTilesetIndex(gid);
			if (tilesetIndex != -1)
			{
				// If valid, set up the map tile with the tileset.
				const Tmx::Tileset* tileset = GetMap()->GetTileset(tilesetIndex);
				tile_map[tileCount] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
			}
			else
			{
				// Otherwise, make it null.
				tile_map[tileCount] = MapTile(gid, 0, (unsigned int)-1);
			}

			pch = strtok(NULL, ",");
			tileCount++;
		}

		free(csv);
	}
};
