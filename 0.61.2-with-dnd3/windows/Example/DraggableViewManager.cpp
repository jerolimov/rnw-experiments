#include "pch.h"
#include "DraggableViewManager.h"
#include "DraggableView.h"

#include "JSValueReader.h"
#include "NativeModules.h"

// Only for testing the view with a background SolidColorBrush
#include <winrt/Windows.UI.Xaml.Media.h>

#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.DragDrop.h>

#include <winrt/Windows.Storage.h>

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

    // IViewManager
    hstring DraggableViewManager::Name() noexcept {
        return L"Draggable";
    }

    FrameworkElement DraggableViewManager::CreateView() noexcept {
        // *winrt::make_self<DroppableView>(m_reactContext);

        // auto const& view = winrt::Windows::UI::Xaml::Controls::Border();

        // auto const& view = DroppableView(m_reactContext);

        auto x = winrt::make_self<DraggableView>(m_reactContext);

        m_view = x->GetView();

        return x->GetView();
    }

    //
    // IViewManagerWithReactContext
    //
    winrt::IReactContext DraggableViewManager::ReactContext() noexcept {
        return m_reactContext;
    }

    void DraggableViewManager::ReactContext(IReactContext reactContext) noexcept {
        m_reactContext = reactContext;
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

    //
    // IViewManagerWithExportedEventTypeConstants
    //
    ConstantProviderDelegate DraggableViewManager::ExportedCustomBubblingEventTypeConstants() noexcept {
        return nullptr;
    }

    ConstantProviderDelegate DraggableViewManager::ExportedCustomDirectEventTypeConstants() noexcept {
        return [](winrt::IJSValueWriter const& constantWriter) {
            WriteCustomDirectEventTypeConstant(constantWriter, L"topDragStarting", L"onDragStarting");
            WriteCustomDirectEventTypeConstant(constantWriter, L"topDropCompleted", L"onDropCompleted");
        };
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
