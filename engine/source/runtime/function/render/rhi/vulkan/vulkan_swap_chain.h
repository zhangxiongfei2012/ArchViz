#pragma once

#include <volk.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <optional>
#include <vector>

namespace ArchViz
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> m_graphics_family;
        std::optional<uint32_t> m_present_family;
        std::optional<uint32_t> m_compute_family;

        bool isComplete() { return m_graphics_family.has_value() && m_present_family.has_value() && m_compute_family.has_value(); }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR        capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR>   presentModes;
    };

    struct VulkanSwapChainBuffer
    {
        VkImage     image;
        VkImageView view;
    };

    class VulkanSwapChain
    {
    public:
        VulkanSwapChain()  = default;
        ~VulkanSwapChain() = default;

        void initSurface(GLFWwindow* window);
        void connect(VkInstance instance, VkPhysicalDevice physical_device, VkDevice device);
        void create(uint32_t width, uint32_t height, bool vsync = false, bool fullscreen = false);
        void cleanup();

        // VkResult acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t* imageIndex);
        // VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE);

    public:
        GLFWwindow*     m_window;
        VkSwapchainKHR  m_swap_chain = VK_NULL_HANDLE;
        VkExtent2D      m_swap_chain_extent;
        VkFormat        m_swap_chain_image_format;
        VkColorSpaceKHR m_color_space;
        uint32_t        m_image_count;
        uint32_t        m_queue_node_index = UINT32_MAX;

        QueueFamilyIndices m_indices;

        std::vector<VkImage>               m_images;
        std::vector<VulkanSwapChainBuffer> m_buffers;

    public:
        VkInstance       m_instance        = VK_NULL_HANDLE;
        VkSurfaceKHR     m_surface         = VK_NULL_HANDLE;
        VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
        VkDevice         m_device          = VK_NULL_HANDLE;
    };
} // namespace ArchViz