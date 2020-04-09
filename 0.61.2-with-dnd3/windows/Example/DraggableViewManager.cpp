#include "pch.h"
#include "DraggableViewManager.h"

#include "JSValueReader.h"
#include "NativeModules.h"

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::Example::implementation {

    // IViewManager
    hstring DraggableViewManager::Name() noexcept {
        return L"Draggable";
    }

    FrameworkElement DraggableViewManager::CreateView() noexcept {
        auto const& view = winrt::Windows::UI::Xaml::Controls::Border();

        view.CanDrag(true);

        return view;
    }

    //
    // IViewManagerWithChildren
    //
    void DraggableViewManager::AddView(FrameworkElement const& parent, UIElement const& child, int64_t /*index*/) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(child);
        }
    }

    void DraggableViewManager::RemoveAllChildren(FrameworkElement const& parent) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(nullptr);
        }
    }

    void DraggableViewManager::RemoveChildAt(FrameworkElement const& parent, int64_t /*index*/) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(nullptr);
        }
    }

    void DraggableViewManager::ReplaceChild(
        FrameworkElement const& parent,
        UIElement const& /*oldChild*/,
        UIElement const& newChild) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(newChild);
        }
    }


    void DraggableViewManager::DispatchCommand(
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
