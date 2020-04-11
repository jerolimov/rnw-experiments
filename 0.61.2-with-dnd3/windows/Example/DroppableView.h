#pragma once

#include "winrt/Microsoft.ReactNative.h"

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
    struct DroppableView {

	public:
		DroppableView(Microsoft::ReactNative::IReactContext const& reactContext);
        void Release();

        winrt::FrameworkElement GetView();

        //
        // Drag and Drop callbacks
        //
        void OnDragEnter(
            const IInspectable& sender,
            const winrt::DragEventArgs& args);
        void OnDragOver(
            const IInspectable& sender,
            const winrt::DragEventArgs& args);
        void OnDragLeave(
            const IInspectable& sender,
            const winrt::DragEventArgs& args);
        IAsyncAction OnDrop(
            const IInspectable& sender,
            const winrt::DragEventArgs& args);
        void OnDropCompleted(
            const Windows::UI::Xaml::UIElement& sender,
            const winrt::DropCompletedEventArgs& args);

	private:
        Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };

        winrt::Windows::UI::Xaml::Controls::Border m_view{ nullptr };

        winrt::event_revoker<winrt::IUIElement> m_dragEnterRevoker;
        winrt::event_revoker<winrt::IUIElement> m_dragOverRevoker;
        winrt::event_revoker<winrt::IUIElement> m_dragLeaveRevoker;
        winrt::event_revoker<winrt::IUIElement> m_dropRevoker;
        winrt::event_revoker<winrt::IUIElement> m_dropCompletedRevoker;

        void updateAcceptedOperation(const winrt::DragEventArgs& args);
    };
}

/*
namespace winrt::Example::factory_implementation {
    struct ReactVideoView : DroppableViewT<ReactVideoView, implementation::ReactVideoView> {};
}
*/
