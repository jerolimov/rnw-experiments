#include "pch.h"
#include "DropableViewManager.h"

#include "JSValueReader.h"
#include "NativeModules.h"

// Only for testing the view with a background SolidColorBrush
#include <winrt/Windows.UI.Xaml.Media.h>

using namespace winrt;

using namespace Microsoft::ReactNative;

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;

namespace winrt::Example::implementation {

    //
    // IViewManager
    //
    hstring DropableViewManager::Name() noexcept {
        return L"Dropable";
    }

    FrameworkElement DropableViewManager::CreateView() noexcept {
        auto const& view = winrt::Windows::UI::Xaml::Controls::Border();

        // auto const& color = winrt::Windows::UI::Colors::Green();
        auto const& color = winrt::Colors::IndianRed();
        auto const& brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        view.Background(brush);

        // view.BorderBrush(brush);

        // view.BorderBrush(COLOR_ACTIVEBORDER);
        // view.BorderThickness(winrt::Windows::UI::Xaml::Thickness());

        view.AllowDrop(true);
        m_dragEnterRevoker = view.DragEnter(winrt::auto_revoke, { this, &DropableViewManager::OnDragEnter });
        m_dragOverRevoker = view.DragOver(winrt::auto_revoke, { this, &DropableViewManager::OnDragOver });
        m_dragLeaveRevoker = view.DragLeave(winrt::auto_revoke, { this, &DropableViewManager::OnDragLeave });

        return view;
    }

    void DropableViewManager::OnDragEnter(
        const IInspectable& sender,
        const DragEventArgs& args) {

        if (auto const& border = sender.try_as<Border>()) {
            m_reactContext.DispatchEvent(
                border,
                L"topLoadingStart",
                [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                    eventDataWriter.WriteObjectBegin();
                    eventDataWriter.WriteObjectEnd();
                });
        }
    }

    void DropableViewManager::OnDragOver(
        const IInspectable& sender,
        const DragEventArgs& args) {

    }

    void DropableViewManager::OnDragLeave(
        const IInspectable& sender,
        const DragEventArgs& args) {

    }

    //
    // IViewManagerWithReactContext
    //
    winrt::IReactContext DropableViewManager::ReactContext() noexcept {
        return m_reactContext;
    }

    void DropableViewManager::ReactContext(IReactContext reactContext) noexcept {
        m_reactContext = reactContext;
    }

    //
    // IViewManagerWithChildren
    //
    void DropableViewManager::AddView(FrameworkElement const& parent, UIElement const& child, int64_t /*index*/) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(child);
        }
    }

    void DropableViewManager::RemoveAllChildren(FrameworkElement const& parent) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(nullptr);
        }
    }

    void DropableViewManager::RemoveChildAt(FrameworkElement const& parent, int64_t /*index*/) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(nullptr);
        }
    }

    void DropableViewManager::ReplaceChild(
        FrameworkElement const& parent,
        UIElement const& /*oldChild*/,
        UIElement const& newChild) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(newChild);
        }
    }


    void DropableViewManager::DispatchCommand(
        FrameworkElement const& view,
        int64_t commandId,
        winrt::Microsoft::ReactNative::IJSValueReader const& commandArgsReader) noexcept {
        if (auto control = view.try_as<winrt::Windows::UI::Xaml::Controls::Border>()) {
            if (commandId == 0) {
                const JSValueArray& commandArgs = JSValue::ReadArrayFrom(commandArgsReader);
                // Execute command
            }
        }
    }

}
