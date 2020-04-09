#pragma once

#include "winrt/Microsoft.ReactNative.h"

namespace winrt::Example::implementation {

    struct DraggableViewManager : winrt::implements<
        DraggableViewManager,
        winrt::Microsoft::ReactNative::IViewManager,
        winrt::Microsoft::ReactNative::IViewManagerWithChildren> {
    public:
        DraggableViewManager() = default;

        // IViewManager
        winrt::hstring Name() noexcept;

        winrt::Windows::UI::Xaml::FrameworkElement CreateView() noexcept;

        //
        // IViewManagerWithChildren
        //
        void AddView(
            winrt::Windows::UI::Xaml::FrameworkElement const& parent,
            winrt::Windows::UI::Xaml::UIElement const& child,
            int64_t index) noexcept;
        void RemoveAllChildren(
            winrt::Windows::UI::Xaml::FrameworkElement const& parent) noexcept;
        void RemoveChildAt(
            winrt::Windows::UI::Xaml::FrameworkElement const& parent,
            int64_t index) noexcept;
        void ReplaceChild(
            winrt::Windows::UI::Xaml::FrameworkElement const& parent,
            winrt::Windows::UI::Xaml::UIElement const& oldChild,
            winrt::Windows::UI::Xaml::UIElement const& newChild) noexcept;



        void DispatchCommand(
            winrt::Windows::UI::Xaml::FrameworkElement const& view,
            int64_t commandId,
            winrt::Microsoft::ReactNative::IJSValueReader const& commandArgsReader) noexcept;
    };

}
