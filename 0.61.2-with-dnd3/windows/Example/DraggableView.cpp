#include "pch.h"

#include "DraggableView.h"

#include <winrt/Microsoft.ReactNative.h>

#include <winrt/Windows.Foundation.h>

#include <winrt/Windows.UI.Core.h>

#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.DragDrop.h>

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Provider.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Storage.Pickers.h>

#include <unknwn.h>
#include <list>

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
        m_uiDispatcher = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread().Dispatcher();

        m_view = winrt::Windows::UI::Xaml::Controls::Border();

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

        // auto file = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\package.json");
        // auto uri = co_await winrt::Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(Windows::Foundation::Uri(L"example:///unknown_file.xml"));
        // auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\node_modules");

        // std::vector<winrt::Windows::Storage::IStorageItem> files{ file };
        
        auto const& data = args.Data();

        args.AllowedOperations(winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy);

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

        data.SetDataProvider(
            winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::StorageItems(),
            { this, &DraggableView::OnDataRequested }
        );
        
        // data.ShareCompleted???

        DispatchEvent(
            L"topDragStarting",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WriteObjectEnd();
            }
        );
    }
        
    fire_and_forget DraggableView::OnDataRequested(
        Windows::ApplicationModel::DataTransfer::DataProviderRequest const request
    ) {
        _RPT0(_CRT_WARN, "DraggableView::OnDataRequested\n");

        auto formatId = request.FormatId();
        auto deferral = request.GetDeferral();

        _RPT1(_CRT_WARN, "- formatId: %sl\n", formatId);

        Sleep(3000);

        // auto file2 = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\package.json");

        /*
        try {
            _RPT0(_CRT_WARN, "installedLocation path??\n");

            Windows::Storage::StorageFolder installedLocation1 { Windows::ApplicationModel::Package::Current().InstalledLocation() };

            _RPT1(_CRT_WARN, "installedLocation path 1: %ls\n", installedLocation1.Path().c_str());

            Windows::Storage::StorageFolder installedLocation2 = Windows::ApplicationModel::Package::Current().InstalledLocation();

            _RPT1(_CRT_WARN, "installedLocation path 2: %ls\n", installedLocation2.Path().c_str());
        }
        catch (const hresult_error& ex) {
            _RPT2(_CRT_WARN, "installedLocation failed: %i %ls\n", ex.code(), ex.message().c_str());
            _RPT2(_CRT_WARN, "installedLocation failed: %u %ls\n", ex.code(), ex.message().c_str());
        }
        */

        try {
            _RPT0(_CRT_WARN, "load file async...\n");

            // auto file = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\package.json");
            // auto file = { co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\package.json") };

            auto localFolder = Windows::Storage::ApplicationData::Current().LocalFolder();
            _RPT1(_CRT_WARN, "localFolder: %ls\n", localFolder.Path().c_str());

            // auto tempFile = co_await localFolder.CreateFileAsync(L"sample.txt", Windows::Storage::CreationCollisionOption::ReplaceExisting);
            // _RPT1(_CRT_WARN, "file: %ls\n", tempFile.Path().c_str());
            // co_await Windows::Storage::FileIO::WriteTextAsync(tempFile, L"Test Text!");


            auto files = co_await localFolder.GetFilesAsync();

            _RPT0(_CRT_WARN, "files selected\n");
            _RPT1(_CRT_WARN, "files count: %i\n", files.Size());
            // _RPT1(_CRT_WARN, "files count: %ls\n", files.First().Current().Path().c_str());

            // std::array<Windows::Storage::IStorageItem, 1> storageFiles = { tempFile };

            // IVectorView<Windows::Storage::IStorageItem> pickedFiles = co_await filePicker.PickMultipleFilesAsync();
            // requestData.SetStorageItems(storageItems.as<IIterable<IStorageItem>>());


            // _RPT1(_CRT_WARN, "files count: %i\n", storageItems.Size());
            // _RPT1(_CRT_WARN, "files count: %ls\n", storageItems.First().Current().Path().c_str());

            m_data = winrt::Windows::ApplicationModel::DataTransfer::DataPackage();

            // m_data.SetStorageItems({ storageFiles.begin(), storageFiles.end() });
            
            m_data.SetStorageItems(files.as<IIterable<Windows::Storage::IStorageItem>>());

            
            auto x = co_await m_data.GetView().GetStorageItemsAsync();
            _RPT1(_CRT_WARN, "files count: %i\n", x.Size());
            _RPT1(_CRT_WARN, "files count: %ls\n", x.First().Current().Path().c_str());


            request.SetData(files);


            _RPT0(_CRT_WARN, "load file done\n");
        }
        catch (const hresult_error& ex) {
            _RPT2(_CRT_WARN, "load file failed: %i %ls\n", ex.code(), ex.message().c_str());
            _RPT2(_CRT_WARN, "load file failed: %u %ls\n", ex.code(), ex.message().c_str());
        }

        /*
        try {
            _RPT0(_CRT_WARN, "load folder async...\n");
            auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(L"C:\git\\rnw-experiments\\0.61.2-with-dnd3\\node_modules");
            _RPT0(_CRT_WARN, "load folder done\n");
        }
        catch (const hresult_error& ex) {
            _RPT0(_CRT_WARN, "load folder failed\n");
        }

        try {
            _RPT0(_CRT_WARN, "load picturesLibrary async...\n");
            auto picturesLibrary = co_await winrt::Windows::Storage::KnownFolders::GetFolderForUserAsync(nullptr, winrt::Windows::Storage::KnownFolderId::PicturesLibrary);
            _RPT0(_CRT_WARN, "load picturesLibrary done\n");
        }
        catch (const hresult_error& ex) {
            _RPT0(_CRT_WARN, "load picturesLibrary failed\n");
        }
        */

        _RPT0(_CRT_WARN, "setData\n");
        // request.SetData(winrt::box_value(L"hallo"));

        /*
        DispatchEventOnUIThread(
            L"topDropRequested",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();
                eventDataWriter.WriteObjectEnd();
            }
        );
        */

        deferral.Complete();
    }

    void DraggableView::OnDropCompleted(
        const winrt::UIElement& sender,
        const winrt::DropCompletedEventArgs& args) {

        _RPT0(_CRT_WARN, "DraggableView::OnDropCompleted\n");

        DispatchEvent(
            L"topDropCompleted",
            [&](winrt::IJSValueWriter const& eventDataWriter) noexcept {
                eventDataWriter.WriteObjectBegin();

                eventDataWriter.WritePropertyName(L"result");
                switch (args.DropResult())
                {
                case winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::None:
                    eventDataWriter.WriteString(L"none");
                    break;
                case winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy:
                    eventDataWriter.WriteString(L"copy");
                    break;
                case winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Move:
                    eventDataWriter.WriteString(L"move");
                    break;
                case winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Link:
                    eventDataWriter.WriteString(L"link");
                    break;
                default:
                    eventDataWriter.WriteString(L"unknown");
                    break;
                }

                eventDataWriter.WriteObjectEnd();
            }
        );
    }

    void DraggableView::DispatchEvent(
        param::hstring const& eventName,
        Microsoft::ReactNative::JSValueArgWriter const& eventDataArgWriter
    ) {
        m_reactContext.DispatchEvent(m_view, eventName, eventDataArgWriter);
    }

    void DraggableView::DispatchEventOnUIThread(
        param::hstring const& eventName,
        Microsoft::ReactNative::JSValueArgWriter const& eventDataArgWriter
    ) {
        m_uiDispatcher.RunAsync(
            winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
            // https://stackoverflow.com/questions/26903602/an-enclosing-function-local-variable-cannot-be-referenced-in-a-lambda-body-unles
            [&]() {
                DispatchEvent(eventName, eventDataArgWriter);
            }
        );
    }
}
