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

        auto const& color = winrt::Colors::Green();
        auto const& brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        m_view.Background(brush);

        m_view.CanDrag(true);
        m_view.DragStarting({ this, &DraggableView::OnDragStarting });
        m_view.DropCompleted({ this, &DraggableView::OnDropCompleted });

        // m_view.Click({ this, &DraggableView::OnDropCompleted });

        /*
        m_dragStartingRevoker = m_view.DragStarting(winrt::auto_revoke, { this, &DraggableView::OnDragStarting });
        m_dropCompletedRevoker = m_view.DropCompleted(winrt::auto_revoke, { this, &DraggableView::OnDropCompleted });
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
    void DraggableView::OnDragStarting(
        const winrt::UIElement& sender,
        const winrt::DragStartingEventArgs& args) {

        _RPT0(_CRT_WARN, "DraggableView::OnDragStarting\n");

        auto color = winrt::Colors::Red();
        auto brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        m_view.Background(brush);

        // auto file = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\package.json");
        // auto uri = co_await winrt::Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(Windows::Foundation::Uri(L"example:///unknown_file.xml"));
        // auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\node_modules");

        // std::vector<winrt::Windows::Storage::IStorageItem> files{ file };
        

        auto const& data = args.Data();

        // args.AllowedOperations(winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy);

        data.RequestedOperation(winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy);

        // data.SetText(L"Hello world!");

        /*
        data.Properties().FileTypes().Append(L"");

        data.SetData(L"Shell IDList Array", winrt::box_value(L"custom?!"));
        data.SetData(L"UsingDefaultDragImage", winrt::box_value(L"custom?!"));
        data.SetData(L"DragImageBits", winrt::box_value(L"custom?!"));
        data.SetData(L"DragContext", winrt::box_value(L"custom?!"));
        data.SetData(L"DragSourceHelperFlags", winrt::box_value(L"custom?!"));
        data.SetData(L"InShellDragLoop", winrt::box_value(L"custom?!"));
        data.SetData(L"FileDrop", winrt::box_value(L"custom?!"));
        data.SetData(L"FileName", winrt::box_value(L"custom?!"));
        data.SetData(L"FileContents", winrt::box_value(L"custom?!"));
        data.SetData(L"FileNameW", winrt::box_value(L"custom?!"));
        data.SetData(L"FileGroupDescriptorW", winrt::box_value(L"custom?!"));
        data.SetData(L"IsShowingLayered", winrt::box_value(L"custom?!"));
        data.SetData(L"DragWindow", winrt::box_value(L"custom?!"));
        data.SetData(L"IsComputingImage", winrt::box_value(L"custom?!"));
        data.SetData(L"DropDescription", winrt::box_value(L"custom?!"));
        data.SetData(L"DisableDragText", winrt::box_value(L"custom?!"));
        data.SetData(L"ComputedDragImage", winrt::box_value(L"custom?!"));
        data.SetData(L"IsShowingText", winrt::box_value(L"custom?!"));
        */

        // data.SetStorageItems(files);

        // data.AddStorageItems(file);
    
        // TODO??? data.SetDataProvider()

        // auto storageItemsKey = winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text;

        data.SetDataProvider(L"Text", { this, &DraggableView::OnDataRequested });
        
        // data.ShareCompleted???

        m_reactContext.DispatchEvent(
            m_view,
            L"topDragStarting",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WriteObjectEnd();
            });
    }

    void DraggableView::OnDropCompleted(
        const winrt::UIElement& sender,
        const winrt::DropCompletedEventArgs& args) {

        _RPT0(_CRT_WARN, "DraggableView::OnDropCompleted\n");

        auto color = winrt::Colors::Green();
        auto brush = winrt::Windows::UI::Xaml::Media::SolidColorBrush(color);
        m_view.Background(brush);

        auto result = args.DropResult();

        m_reactContext.DispatchEvent(
            m_view,
            L"topDropCompleted",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WriteObjectEnd();
            });
    }

    fire_and_forget DraggableView::OnDataRequested(
        Windows::ApplicationModel::DataTransfer::DataProviderRequest const& request) {

        _RPT0(_CRT_WARN, "DraggableView::OnDataRequested\n");

        auto deferral = request.GetDeferral();

        

        try {
            _RPT0(_CRT_WARN, "load file async...\n");
            // auto file = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\package.json");
            // auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\node_modules");

            auto picturesLibrary = co_await winrt::Windows::Storage::KnownFolders::GetFolderForUserAsync(nullptr /* current user */, winrt::Windows::Storage::KnownFolderId::PicturesLibrary);

            // Windows::Storage::StorageFolder folder{ co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\node_modules") };

            _RPT0(_CRT_WARN, "load file done\n");
        }
        catch (const hresult_error& ex) {
            _RPT0(_CRT_WARN, "load file failed\n");
        }

        _RPT0(_CRT_WARN, "setData\n");

        request.SetData(winrt::box_value(L"hallo"));

        deferral.Complete();
    }
}
