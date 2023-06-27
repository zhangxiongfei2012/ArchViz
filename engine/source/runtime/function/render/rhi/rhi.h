#pragma once
#include "runtime/function/render/rhi/rhi_struct.h"

#include <volk.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// #include <vk_mem_alloc.h>

#include <functional>
#include <memory>
#include <vector>

namespace ArchViz
{
    class WindowSystem;

    struct RHIInitInfo
    {
        std::shared_ptr<WindowSystem> window_system;
    };

    class RHI
    {
    public:
        virtual ~RHI() = 0;

        virtual void initialize(RHIInitInfo initialize_info) = 0;
        virtual void prepareContext()                        = 0;

        // virtual void createSwapchain()               = 0;
        // virtual void recreateSwapchain()             = 0;
        // virtual void createSwapchainImageViews()     = 0;
        // virtual void createFramebufferImageAndView() = 0;

        // // destory
        virtual void clear() = 0;
        // virtual void clearSwapchain() = 0;

    private:
    };

    inline RHI::~RHI() = default;
} // namespace ArchViz
