#include "runtime/platform/file_system/vfs.h"
#include "runtime/resource/asset_manager/asset_manager.h"
#include "runtime/resource/config_manager/config_manager.h"

#include "runtime/function/render/rhi/spirv_parser.h"
#include "runtime/function/render/rhi/vulkan/utils/vulkan_shader_utils.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

using namespace ArchViz;
using namespace std;

int main(int argc, char** argv)
{
    std::filesystem::path executable_path(argv[0]);
    std::filesystem::path config_file_path = executable_path.parent_path() / "../ArchVizEditor.ini";
    cout << config_file_path << endl;

    std::shared_ptr<ConfigManager> config_manager = std::make_shared<ConfigManager>();
    config_manager->initialize(config_file_path.generic_string());

    std::shared_ptr<AssetManager> asset_manager = std::make_shared<AssetManager>();
    asset_manager->setConfigManager(config_manager);

    VFSConfig config;
    asset_manager->loadAsset<VFSConfig>("config/config.vfs.json", config);
    std::shared_ptr<VFS> vfs = std::make_shared<VFS>();
    vfs->mount(config);

    asset_manager->setVFS(vfs);

    std::vector<uint32_t> vert = VulkanShaderUtils::createShaderModuleFromVFS("shader/glsl/shader_textures.vert", config_manager, asset_manager);
    std::vector<uint32_t> frag = VulkanShaderUtils::createShaderModuleFromVFS("shader/glsl/shader_textures.frag", config_manager, asset_manager);

    SPIRV::ParseResult result;
    std::string name_buffer;
    SPIRV::parse_binary(vert, name_buffer, result);

    return 0;
}
