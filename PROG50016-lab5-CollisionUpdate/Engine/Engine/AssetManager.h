#pragma once
#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <list>
#include "Asset.h"

/**
 * @brief An AssetMapEntry denotes a single Asset entry in the AssetManager's internal storage.
 * 
 */
struct AssetMapEntry
{
	/**
	 * @brief A pointer to the referenced Asset.
	 * 
	 */
	Asset* asset;
	/**
	 * @brief Scene-based reference count for the Asset.
	 * 
	 */
	unsigned int ref_count;
};

class AssetManager {
	DECLARE_SINGLETON(AssetManager)

	/**
	 * @brief Base Asset search directory.
	 * 
	 */
	std::string assetDirectory = "../Assets";

	/**
	 * @brief Boolean to control whether to search recursively.
	 * 
	 */
	bool recursiveSearch = true;

	/**
	 * @brief All the Assets managed by this AssetManager.
	 * 
	 */
	std::map<STRCODE, AssetMapEntry> assets;
public:
	void Destroy();

	void Initialize();

	/**
	 * @brief Add an Asset to the AssetManager's collection of Assets.
	 * 
	 * @param asset Asset to add.
	 */
	void AddAsset(Asset* asset);

	/**
	 * @brief Increase reference count for the given Asset.
	 * 
	 * @param guid Asset to load.
	 */
	void LoadSceneAsset(std::string guid);
	
	/**
	 * @brief Increase reference count for the given Asset.
	 * 
	 * @param id Asset to load. 
	 */
	void LoadSceneAsset(STRCODE id);

	/**
	 * @brief Decrease reference count for the given Asset.
	 * 
	 * @param guid Asset to unload.
	 */
	void UnloadSceneAsset(std::string guid);

	/**
	 * @brief Decrease reference count for the given Asset.
	 * 
	 * @param id Asset to unload.
	 */
	void UnloadSceneAsset(STRCODE id);

	/**
	 * @brief Get a Pointer to a requested Asset.
	 * 
	 * @param guid Asset requested.
	 * @return Asset* Requested Asset if found, or nullptr if not.
	 */
	Asset* GetAsset(std::string guid);

	/**
	 * @brief Get a Pointer to a requested Asset.
	 * 
	 * @param id Asset requested.
	 * @return Asset* Requested Asset if found, or nullptr if not.
	 */
	Asset* GetAsset(STRCODE id);
	
	/**
	 * @brief Remove given Asset from the AssetManager's collection of Assets.
	 * 
	 * @param guid Asset to remove.
	 */
	void RemoveAsset(std::string guid);
	
	/**
	 * @brief Remove given Asset from the AssetManager's collection of Assets.
	 * 
	 * @param id Asset to remove.
	 */
	void RemoveAsset(STRCODE id);

	/**
	 * @brief Load the AssetManager's settings.
	 * 
	 * @param config_file File to get configuration values from.
	 */
	void Load(const std::string& config_file);
};

#endif // !_ASSET_MANAGER_H_