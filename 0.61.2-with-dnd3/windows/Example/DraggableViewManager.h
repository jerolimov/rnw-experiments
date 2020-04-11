#pragma once

#include "winrt/Microsoft.ReactNative.h"

#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Input.h>

namespace winrt {
    using namespace Microsoft::ReactNative;

    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;

    using namespace Windows::UI;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml::Media;
} // namespace winrt

namespace winrt::Example::implementation {

    struct DraggableViewManager : winrt::implements<
        DraggableViewManager,
        winrt::Microsoft::ReactNative::IViewManager,
        winrt::Microsoft::ReactNative::IViewManagerWithReactContext,
        winrt::Microsoft::ReactNative::IViewManagerWithChildren,
        winrt::Microsoft::ReactNative::IViewManagerWithExportedEventTypeConstants> {
    public:
        DraggableViewManager() = default;

        // IViewManager
        winrt::hstring Name() noexcept;

        winrt::Windows::UI::Xaml::FrameworkElement CreateView() noexcept;

        //
        // IViewManagerWithReactContext
        //
        winrt::Microsoft::ReactNative::IReactContext ReactContext() noexcept;
        void ReactContext(winrt::Microsoft::ReactNative::IReactContext reactContext) noexcept;

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

        //
        // IViewManagerWithExportedEventTypeConstants
        //
        winrt::Microsoft::ReactNative::ConstantProviderDelegate ExportedCustomBubblingEventTypeConstants() noexcept;
        winrt::Microsoft::ReactNative::ConstantProviderDelegate ExportedCustomDirectEventTypeConstants() noexcept;



        void DispatchCommand(
            winrt::Windows::UI::Xaml::FrameworkElement const& view,
            int64_t commandId,
            winrt::Microsoft::ReactNative::IJSValueReader const& commandArgsReader) noexcept;


    private:
        winrt::Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
        winrt::Windows::UI::Xaml::UIElement m_view{ nullptr };
    };

}
