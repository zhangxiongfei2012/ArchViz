#pragma once
#include "runtime/function/render/rhi/rhi.h"

#include "runtime/function/render/rhi/vulkan/vulkan_struct.h"

#include <volk.h>

#include <cstdint>
#include <memory>
#include <vector>

namespace ArchViz
{
    class AssetManager;
    class ConfigManager;
    class VulkanDevice;
    class VulkanSwapChain;
    class VulkanPipeline;
    class VulkanRenderPass;
    class VulkanInstance;

    class VulkanRHI : public RHI
    {
    public:
        VulkanRHI()          = default;
        virtual ~VulkanRHI() = default;

        void setConfigManager(std::shared_ptr<ConfigManager> config_manager) override;
        void setAssetManager(std::shared_ptr<AssetManager> asset_manager) override;

        void initialize(RHIInitInfo initialize_info) override;
        void prepareContext() override;

        void clear() override;

    private:
        void createInstance();
        void setupDebugMessenger();
        void createSurface();

        void pickPhysicalDevice();
        void createLogicalDevice();

        void createSwapChain();
        void createImageViews();

        void createRenderPass();
        void createGraphicsPipeline();

        void createFramebuffers();

        void createCommandPool();
        void createCommandBuffer();

        void createSyncObjects();

    private:
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void drawFrame();

    private:
        const bool m_enable_validation_layers = false;

        std::shared_ptr<AssetManager>  m_asset_manager;
        std::shared_ptr<ConfigManager> m_config_manager;

        RHIInitInfo m_initialize_info;

        std::shared_ptr<VulkanInstance>   m_vulkan_instance;
        std::shared_ptr<VulkanDevice>     m_vulkan_device;
        std::shared_ptr<VulkanSwapChain>  m_vulkan_swap_chain;
        std::shared_ptr<VulkanPipeline>   m_vulkan_pipeline;
        std::shared_ptr<VulkanRenderPass> m_vulkan_render_pass;

        std::vector<VkFramebuffer> m_swap_chain_framebuffers;

        VkCommandPool   m_command_pool;
        VkCommandBuffer m_command_buffer;

        VkSemaphore m_image_available_semaphore;
        VkSemaphore m_render_finished_semaphore;
        VkFence     m_in_flight_fence;
    };
} // namespace ArchViz
