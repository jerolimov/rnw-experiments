#include "pch.h"
#include "ReactPackageProvider.h"

#include "NativeModules.h"

#include "DragableViewManager.h"
#include "DropableViewManager.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Example::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
    packageBuilder.AddViewManager(
        L"DragableViewManager", []() { return winrt::make<DragableViewManager>(); }
    );
    packageBuilder.AddViewManager(
        L"DropableViewManager", []() { return winrt::make<DropableViewManager>(); }
    );

    AddAttributedModules(packageBuilder);
}

} // namespace winrt::Example::implementation


