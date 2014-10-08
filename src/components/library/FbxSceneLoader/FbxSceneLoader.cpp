#include "FbxSceneLoader.h"

std::shared_ptr<FbxScene> ResourceLoader<FbxScene>::LoadResource (const std::string &name, ResourceManager<FbxScene> &calling_manager) {
  static FbxManager * gFbxManager = FbxManager::Create();

  FbxImporter * importer = FbxImporter::Create(gFbxManager, "");
  
  // Make a shared_ptr with the destructor of the shared_ptr calling Destroy()
  std::shared_ptr<FbxScene> scene(FbxScene::Create(gFbxManager, ""), [] (FbxScene* scene) {
    scene->Destroy();
  });
  
  std::string error;
  std::string fullName = calling_manager.GetBasePath() + name;

  // Try initializing the file and importing the scene.  Using the default FbxIOSettings for now
  if (importer->Initialize(fullName.c_str())) {
    if (!importer->Import(scene.get())) {
      error = "error encountered while attempting to import scene from file \"" + fullName + "\"";
    }
  } else {
    error = "error encountered while attempting to initialize file \"" + fullName + "\"";
  }
  
  importer->Destroy();
  
  if (!error.empty()) {
    throw ResourceExceptionOfType<FbxScene>(error);
  }
  
  return scene;
}