/* Residual - A 3D game interpreter
 *
 * Residual is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 */

#ifndef GRIM_RESOURCE_H
#define GRIM_RESOURCE_H

#include "common/archive.h"
#include "common/file.h"

#include "engines/grim/object.h"
#include "engines/grim/lua/lua.h"

namespace Grim {

class Bitmap;
class CMap;
class Costume;
class Font;
class KeyframeAnim;
class Material;
class Model;
class EMIModel;
class LipSync;
class TrackedObject;
class SaveGame;
class Skeleton;
class Lab;

typedef ObjectPtr<Material> MaterialPtr;
typedef ObjectPtr<Bitmap> BitmapPtr;
typedef ObjectPtr<Model> ModelPtr;
typedef ObjectPtr<CMap> CMapPtr;
typedef ObjectPtr<KeyframeAnim> KeyframeAnimPtr;
typedef ObjectPtr<Font> FontPtr;
typedef ObjectPtr<LipSync> LipSyncPtr;

class ResourceLoader {
public:
	ResourceLoader();
	~ResourceLoader();

	Bitmap *loadBitmap(const Common::String &fname);
	CMap *loadColormap(const Common::String &fname);
	Costume *loadCostume(const Common::String &fname, Costume *prevCost);
	Font *loadFont(const Common::String &fname);
	KeyframeAnim *loadKeyframe(const Common::String &fname);
	Material *loadMaterial(const Common::String &fname, CMap *c);
	Model *loadModel(const Common::String &fname, CMap *c, Model *parent = NULL);
	EMIModel *loadModelEMI(const Common::String &fname, EMIModel *parent = NULL);
	LipSync *loadLipSync(const Common::String &fname);
	Skeleton *loadSkeleton(const Common::String &fname);
	Common::SeekableReadStream *openNewStreamFile(const char *filename, bool cache = false);
	void uncache(const char *fname);
	bool getFileExists(const Common::String &filename) const;

	ModelPtr getModel(const Common::String &fname, CMap *c);
	CMapPtr getColormap(const Common::String &fname);
	KeyframeAnimPtr getKeyframe(const Common::String &fname);
	LipSyncPtr getLipSync(const Common::String &fname);
	void uncacheModel(Model *m);
	void uncacheColormap(CMap *c);
	void uncacheKeyframe(KeyframeAnim *kf);
	void uncacheLipSync(LipSync *l);

	struct ResourceCache {
		char *fname;
		byte *resPtr;
		uint32 len;
	};

private:
	const Lab *getLab(const Common::String &filename) const;
	Common::SeekableReadStream *loadFile(Common::String &filename) const;
	Common::SeekableReadStream *getFileFromCache(const Common::String &filename);
	ResourceLoader::ResourceCache *getEntryFromCache(const Common::String &filename);
	void putIntoCache(const Common::String &fname, byte *res, uint32 len);

	typedef Common::List<Lab *> LabList;
	LabList _labs;
	Common::SearchSet _files;

	Common::Array<ResourceCache> _cache;
	bool _cacheDirty;
	int32 _cacheMemorySize;

	Common::List<EMIModel *> _emiModels;
	Common::List<Model *> _models;
	Common::List<CMap *> _colormaps;
	Common::List<KeyframeAnim *> _keyframeAnims;
	Common::List<LipSync *> _lipsyncs;
};

extern ResourceLoader *g_resourceloader;

} // end of namespace Grim

#endif
