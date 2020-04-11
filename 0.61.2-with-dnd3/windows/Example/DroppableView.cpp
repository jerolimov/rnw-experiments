#include "pch.h"

#include "DroppableView.h"

#include <winrt/Microsoft.ReactNative.h>

#include <winrt/Windows.Foundation.h>

// Only for testing the view with a background SolidColorBrush
#include <winrt/Windows.UI.Xaml.Media.h>

#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.DragDrop.h>

#include <winrt/Windows.Storage.h>

namespace winrt {
    using namespace Microsoft::ReactNative;
    using namespace Windows::Foundation;
    using namespace Windows::UI;
    using namespace Windows::UI::Popups;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml::Media;
} // namespace winrt

namespace winrt::Example::implementation {

    DroppableView::DroppableView(winrt::IReactContext const& reactContext) {
        _RPT0(_CRT_WARN, "DroppableView::Constructor\n");

        m_reactContext = reactContext;

        m_view = winrt::Windows::UI::Xaml::Controls::Border();

        auto const& color = winrt::Windows::UI::Colors::Green();
        auto const& brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        m_view.Background(brush);

        m_view.AllowDrop(true);

        m_view.DragEnter({ this, &DroppableView::OnDragEnter });
        m_view.DragOver({ this, &DroppableView::OnDragOver });
        m_view.DragLeave({ this, &DroppableView::OnDragLeave });
        m_view.Drop({ this, &DroppableView::OnDrop });
        m_view.DropCompleted({ this, &DroppableView::OnDropCompleted });

        /*
        m_dragEnterRevoker = m_view.DragEnter(winrt::auto_revoke, { this, &DroppableView::OnDragEnter });
        m_dragOverRevoker = m_view.DragOver(winrt::auto_revoke, { this, &DroppableView::OnDragOver });
        m_dragLeaveRevoker = m_view.DragLeave(winrt::auto_revoke, { this, &DroppableView::OnDragLeave });
        m_dropRevoker = m_view.Drop(winrt::auto_revoke, { this, &DroppableView::OnDrop });
        */
        // m_dropCompletedRevoker = m_view.DropCompleted(winrt::auto_revoke, { this, &DroppableView::OnDropCompleted });
    }

    void DroppableView::Release() {
        _RPT0(_CRT_WARN, "DroppableView::Release\n");
    }

    winrt::FrameworkElement DroppableView::GetView() {
        return m_view;
    }

    //
    // Drag and drop callbacks
    //
    void DroppableView::OnDragEnter(
        const IInspectable& sender,
        const DragEventArgs& args) {

        args.Handled(true);
        updateAcceptedOperation(args);

        auto color = winrt::Colors::Red();
        auto brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        m_view.Background(brush);

        m_reactContext.DispatchEvent(
            m_view,
            L"topDragEnter",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WriteObjectEnd();
            });
    }

    void DroppableView::OnDragOver(
        const IInspectable& sender,
        const DragEventArgs& args) {

        if (auto const& view = sender.try_as<Border>()) {
            m_reactContext.DispatchEvent(
                view,
                L"topDragOver",
                [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                    eventDataWriter.WriteObjectBegin();
                    eventDataWriter.WriteObjectEnd();
                });
        }
    }

    void DroppableView::OnDragLeave(
        const IInspectable& sender,
        const DragEventArgs& args) {

        auto color = winrt::Colors::Green();
        auto brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        m_view.Background(brush);

        m_reactContext.DispatchEvent(
            m_view,
            L"topDragLeave",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WriteObjectEnd();
            });
    }

    IAsyncAction DroppableView::OnDrop(
        const IInspectable& sender,
        const DragEventArgs& args) {

        // TODO: args.Handled(true);

        auto dataView = args.DataView();

        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::IStorageItem> storageItems;

        if (dataView != nullptr) {

            auto formats = dataView.AvailableFormats();

            _RPT0(_CRT_WARN, "Formats:\n");
            for (uint32_t i = 0; i < formats.Size(); i++) {
                _RPT1(_CRT_WARN, "- %ls\n", formats.GetAt(i).c_str());
            }

            if (dataView.Contains(L"FileDrop")) {
                try {
                    storageItems = co_await dataView.GetStorageItemsAsync();

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

        

        m_reactContext.DispatchEvent(
            m_view,
            L"topDrop",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WritePropertyName(L"files");
                {
                    eventDataWriter.WriteArrayBegin();
                    for (uint32_t i = 0; i < storageItems.Size(); i++) {
                        auto storageItem = storageItems.GetAt(i);
                        eventDataWriter.WriteString(storageItem.Path());
                    }
                    eventDataWriter.WriteArrayEnd();
                }
                eventDataWriter.WriteObjectEnd();
            });
    }

    void DroppableView::OnDropCompleted(
        const Windows::UI::Xaml::UIElement& sender,
        const winrt::DropCompletedEventArgs& args) {

        m_reactContext.DispatchEvent(
            m_view,
            L"topDropCompleted",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WriteObjectEnd();
            });
    }

    void DroppableView::updateAcceptedOperation(const DragEventArgs& args) {
        auto dataView = args.DataView();

        if (dataView != nullptr) {
            if (dataView.Contains(L"FileDrop")) {
                args.AcceptedOperation(winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy);
                return;
            }
        }

        args.AcceptedOperation(winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::None);
    }
}
