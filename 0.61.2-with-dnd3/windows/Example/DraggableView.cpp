#include "pch.h"

#include "DraggableView.h"

#include <winrt/Microsoft.ReactNative.h>

#include <winrt/Windows.Foundation.h>

// Only for testing the view with a background SolidColorBrush
#include <winrt/Windows.UI.Xaml.Media.h>

#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.DragDrop.h>

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Provider.h>

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

    DraggableView::DraggableView(winrt::IReactContext const& reactContext) {
        _RPT0(_CRT_WARN, "DroppableView::Constructor\n");

        m_reactContext = reactContext;

        m_view = winrt::Windows::UI::Xaml::Controls::Border();

        auto const& color = winrt::Colors::AliceBlue();
        auto const& brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        m_view.Background(brush);

        m_view.CanDrag(true);
        m_view.DragStarting({ this, &DraggableView::OnDragStarting });

        /*
        m_dragStartingRevoker = m_view.DragStarting(winrt::auto_revoke, { this, &DraggableView::OnDragStarting });
        */
    }

    void DraggableView::Release() {
        _RPT0(_CRT_WARN, "DraggableView::Release\n");
    }

    winrt::FrameworkElement DraggableView::GetView() {
        return m_view;
    }

    //
    // Drag and drop callbacks
    //
    IAsyncAction DraggableView::OnDragStarting(
        const winrt::UIElement& sender,
        const winrt::DragStartingEventArgs& args) {

        _RPT0(_CRT_WARN, "DraggableView::OnDragStarting\n");

        auto color = winrt::Colors::Red();
        auto brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        m_view.Background(brush);

        auto file = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\package.json");
        auto uri = co_await winrt::Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(Windows::Foundation::Uri(L"example:///unknown_file.xml"));
        auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\node_modules");

        std::vector<winrt::Windows::Storage::IStorageItem> files{ file };

        args.Data().SetData(L"FileDrop", winrt::box_value(L"custom?!"));
        args.Data().SetData(L"CustomFileDrop", winrt::box_value(L"custom?!"));

        args.Data().SetStorageItems(files);

        /*
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::IStorageItem> storageItems = {
            file,
            uri,,
        };
        */

        m_reactContext.DispatchEvent(
            m_view,
            L"topDragStarting",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WriteObjectEnd();
            });
    }

}
