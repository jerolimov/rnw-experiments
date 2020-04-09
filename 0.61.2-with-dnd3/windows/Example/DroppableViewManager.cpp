#include "pch.h"
#include "DroppableViewManager.h"

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

    //
    // IViewManager
    //
    hstring DroppableViewManager::Name() noexcept {
        return L"Droppable";
    }

    FrameworkElement DroppableViewManager::CreateView() noexcept {
        auto const& view = winrt::Windows::UI::Xaml::Controls::Border();

        // auto const& color = winrt::Windows::UI::Colors::Green();
        auto const& color = winrt::Colors::IndianRed();
        auto const& brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        view.Background(brush);

        // view.BorderBrush(brush);

        // view.BorderBrush(COLOR_ACTIVEBORDER);
        // view.BorderThickness(winrt::Windows::UI::Xaml::Thickness());

        view.AllowDrop(true);
        m_dragEnterRevoker = view.DragEnter(winrt::auto_revoke, { this, &DroppableViewManager::OnDragEnter });
        m_dragOverRevoker = view.DragOver(winrt::auto_revoke, { this, &DroppableViewManager::OnDragOver });
        m_dragLeaveRevoker = view.DragLeave(winrt::auto_revoke, { this, &DroppableViewManager::OnDragLeave });
        m_dropRevoker = view.Drop(winrt::auto_revoke, { this, &DroppableViewManager::OnDrop });

        // m_dropCompletedRevoker = 
        view.DropCompleted(winrt::auto_revoke, { this, &DroppableViewManager::OnDropCompleted });

        
        return view;
    }

    void DroppableViewManager::OnDragEnter(
        const IInspectable& sender,
        const DragEventArgs& args) {

        args.Handled(true);
        args.AcceptedOperation(winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy);

        if (auto const& border = sender.try_as<Border>()) {
            m_reactContext.DispatchEvent(
                border,
                L"topDragEnter",
                [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                    eventDataWriter.WriteObjectBegin();
                    eventDataWriter.WriteObjectEnd();
                });
        }
    }

    void DroppableViewManager::OnDragOver(
        const IInspectable& sender,
        const DragEventArgs& args) {

        // folly::dynamic json = folly::dynamic::object()("target", target);

        if (auto const& border = sender.try_as<Border>()) {
            m_reactContext.DispatchEvent(
                border,
                L"topDragOver",
                [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                    eventDataWriter.WriteObjectBegin();
                    eventDataWriter.WriteObjectEnd();
                });
        }
    }

    void DroppableViewManager::OnDragLeave(
        const IInspectable& sender,
        const DragEventArgs& args) {

        if (auto const& border = sender.try_as<Border>()) {
            m_reactContext.DispatchEvent(
                border,
                L"topDragLeave",
                [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                    eventDataWriter.WriteObjectBegin();
                    eventDataWriter.WriteObjectEnd();
                });
        }
    }

    fire_and_forget DroppableViewManager::OnDrop(
        const IInspectable& sender,
        const DragEventArgs& args) {

        args.Handled(true);

        auto data = args.Data();
        auto dataView = args.DataView();

        if (data != nullptr) {

            auto formats = data.GetView().AvailableFormats();

        }
        if (dataView != nullptr) {
            
            auto formats = dataView.AvailableFormats();

            _RPT0(_CRT_WARN, "Formats:\n");
            for (uint32_t i = 0; i < formats.Size(); i++) {
                _RPT1(_CRT_WARN, "- %ls\n", formats.GetAt(i).c_str());
            }

            if (dataView.Contains(L"FileDrop")) {
                try {
                    auto storageItems = co_await dataView.GetStorageItemsAsync();
                    for (uint32_t i = 0; i < storageItems.Size(); i++) {
                        auto storageItem = storageItems.GetAt(i);

                        _RPT1(_CRT_WARN, "- %ls   path: %ls\n", storageItem.Name().c_str(), storageItem.Path().c_str());
                    }
                }
                catch (...) {
                }
            }

            /*
            try {
                auto uri = co_await dataView.GetUriAsync();
                auto uriStr = uri.ToString();
                auto uriCStr = uri.ToString().c_str();

                _RPT1(_CRT_WARN, "uri: %ls\n", uriCStr);
            }
            catch (...) {}
            */

            /*
            try {
                auto text = co_await dataView.GetTextAsync();

                _RPT1(_CRT_WARN, "text: %ls\n", text.c_str());
            }
            catch (...) {}
            */

            // }

        }

        if (auto const& border = sender.try_as<Border>()) {
            m_reactContext.DispatchEvent(
                border,
                L"topDrop",
                [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                    eventDataWriter.WriteObjectBegin();
                    eventDataWriter.WriteObjectEnd();
                });
        }
    }

    void DroppableViewManager::OnDropCompleted(
        const Windows::UI::Xaml::UIElement& sender,
        const winrt::DropCompletedEventArgs& args) {

        if (auto const& border = sender.try_as<Border>()) {
            m_reactContext.DispatchEvent(
                border,
                L"topDropCompleted",
                [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                    eventDataWriter.WriteObjectBegin();
                    eventDataWriter.WriteObjectEnd();
                });
        }
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
