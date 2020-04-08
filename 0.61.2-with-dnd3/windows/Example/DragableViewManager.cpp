#include "pch.h"
#include "DragableViewManager.h"

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
    hstring DragableViewManager::Name() noexcept {
        return L"Dragable";
    }

    FrameworkElement DragableViewManager::CreateView() noexcept {
        auto const& view = winrt::Windows::UI::Xaml::Controls::Border();

        view.CanDrag(true);

        return view;
    }

    //
    // IViewManagerWithChildren
    //
    void DragableViewManager::AddView(FrameworkElement const& parent, UIElement const& child, int64_t /*index*/) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(child);
        }
    }

    void DragableViewManager::RemoveAllChildren(FrameworkElement const& parent) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(nullptr);
        }
    }

    void DragableViewManager::RemoveChildAt(FrameworkElement const& parent, int64_t /*index*/) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(nullptr);
        }
    }

    void DragableViewManager::ReplaceChild(
        FrameworkElement const& parent,
        UIElement const& /*oldChild*/,
        UIElement const& newChild) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(newChild);
        }
    }


    void DragableViewManager::DispatchCommand(
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
