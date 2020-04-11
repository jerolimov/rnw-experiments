#include "pch.h"

#include "DroppableViewManager.h"

#include "JSValueReader.h"
#include "NativeModules.h"

// Only for testing the view with a background SolidColorBrush
#include <winrt/Windows.UI.Xaml.Media.h>

#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.DragDrop.h>

#include <winrt/Windows.Storage.h>

#include "DroppableView.h"

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

    DroppableViewManager::DroppableViewManager() {
    }

    //
    // IViewManager
    //
    hstring DroppableViewManager::Name() noexcept {
        return L"Droppable";
    }

    FrameworkElement DroppableViewManager::CreateView() noexcept {
        // *winrt::make_self<DroppableView>(m_reactContext);

        // auto const& view = winrt::Windows::UI::Xaml::Controls::Border();

        // auto const& view = DroppableView(m_reactContext);

        auto x = winrt::make_self<DroppableView>(m_reactContext);

        m_view = x->GetView();

        return x->GetView();
    }

    //
    // IViewManagerWithReactContext
    //
    winrt::IReactContext DroppableViewManager::ReactContext() noexcept {
        return m_reactContext;
    }

    void DroppableViewManager::ReactContext(IReactContext reactContext) noexcept {
        m_reactContext = reactContext;
    }

    //
    // IViewManagerWithChildren
    //
    void DroppableViewManager::AddView(FrameworkElement const& parent, UIElement const& child, int64_t /*index*/) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(child);
        }
    }

    void DroppableViewManager::RemoveAllChildren(FrameworkElement const& parent) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(nullptr);
        }
    }

    void DroppableViewManager::RemoveChildAt(FrameworkElement const& parent, int64_t /*index*/) noexcept {
        if (auto const& border = parent.try_as<Border>()) {
            border.Child(nullptr);
        }
    }

    void DroppableViewManager::ReplaceChild(
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
    ConstantProviderDelegate DroppableViewManager::ExportedCustomBubblingEventTypeConstants() noexcept {
        return nullptr;
    }

    ConstantProviderDelegate DroppableViewManager::ExportedCustomDirectEventTypeConstants() noexcept {
        return [](winrt::IJSValueWriter const& constantWriter) {
            WriteCustomDirectEventTypeConstant(constantWriter, L"topDragEnter", L"onDragEnter");
            WriteCustomDirectEventTypeConstant(constantWriter, L"topDragOver", L"onDragOver");
            WriteCustomDirectEventTypeConstant(constantWriter, L"topDragLeave", L"onDragLeave");
            WriteCustomDirectEventTypeConstant(constantWriter, L"topDrop", L"onDrop");
            WriteCustomDirectEventTypeConstant(constantWriter, L"topDropCompleted", L"onDropCompleted");
        };
    }


    void DroppableViewManager::DispatchCommand(
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
