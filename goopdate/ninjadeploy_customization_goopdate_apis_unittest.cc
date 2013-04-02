// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ========================================================================
//
// Tests the constants that vary depending on the customization of Omaha.
// The test checks for the Google Update variations, but can be modified for
// your purposes.

#include <windows.h>
#include <tchar.h>
#include <atlbase.h>
#include <oleauto.h>
#include "omaha/base/browser_utils.h"
#include "omaha/base/utils.h"
#include "omaha/common/const_goopdate.h"
#include "goopdate/omaha3_idl.h"
#include "omaha/testing/omaha_customization_test.h"

// TODO(omaha): Add tests for to detect interface changes that would require
// rolling _OMAHA3_IDL_PROXY_CLSID_IS. These include:
// 1) interface changes invovlving the number or signature of methods
// 2) or that new interfaces have been added
// For #2, we already have the InvalidIndex test for interfaces in the TypeLib,
// so we just need to add checks for interfaces not in the TypeLib.
//
// ITypeLib and ITypeInfo methods might be useful. See:
// http://msdn.microsoft.com/en-us/library/aa912648.aspx
// http://msdn.microsoft.com/en-us/library/aa909031.aspx
//
// I do not know how to get information about interfaces not in a TypeLib.
// Fortunately, most Omaha 3 interfaces are in one.
//
// If we can not get all the information we need, we can always save a "golden"
// idl.h file and diff against it.


// Most of the tests are intentionally not using the omaha namespace. Most of
// the values being tested are not in this namespace, and being in the global
// namespace is required by TEST_GU_INT_F to catch conflicts with Google types
// when building non-Google versions.

class NinjaDeployCustomizationGoopdateComInterfaceTest
    : public OmahaCustomizationTypeLibComInterfaceTest {
 protected:
  NinjaDeployCustomizationGoopdateComInterfaceTest()
      : OmahaCustomizationTypeLibComInterfaceTest(omaha::kOmahaDllName) {
  }
};

// Fixture for testing interfaces that are not in a TypeLib.
// We can only verify the uuid of the interfaces and classes.
class NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest
    : public testing::Test {
};

//
// Omaha 3 COM Constants.
//

namespace omaha {

// TODO(omaha): We should probably move these to a separate
// const_com_customization.h in goopdate\.
TEST(NinjaDeployCustomizationTest, Constants_ComProgIds) {
  EXPECT_GU_STREQ(_T("GoogleUpdate.OnDemandCOMClassUser"), kProgIDOnDemandUser);
  EXPECT_GU_STREQ(_T("GoogleUpdate.OnDemandCOMClassMachine"),
                  kProgIDOnDemandMachine);
  EXPECT_GU_STREQ(_T("GoogleUpdate.OnDemandCOMClassSvc"), kProgIDOnDemandSvc);

  EXPECT_GU_STREQ(_T("GoogleUpdate.Update3WebUser"), kProgIDUpdate3WebUser);
  EXPECT_GU_STREQ(_T("GoogleUpdate.Update3WebMachine"),
                  kProgIDUpdate3WebMachine);
  EXPECT_GU_STREQ(_T("GoogleUpdate.Update3WebSvc"), kProgIDUpdate3WebSvc);

  EXPECT_GU_STREQ(_T("GoogleUpdate.CoreClass"), kProgIDGoogleUpdateCoreService);

  EXPECT_GU_STREQ(_T("GoogleUpdate.ProcessLauncher"), kProgIDProcessLauncher);
}

}  // namespace omaha

//
// Omaha 3 COM Interfaces Enums.
//

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest, BrowserType) {
  EXPECT_EQ(0, BROWSER_UNKNOWN);
  EXPECT_EQ(1, BROWSER_DEFAULT);
  EXPECT_EQ(2, BROWSER_INTERNET_EXPLORER);
  EXPECT_EQ(3, BROWSER_FIREFOX);
  EXPECT_EQ(4, BROWSER_CHROME);
}

// There are two different BrowserType definitions, one in the IDL and one
// in browser_utils. Verify they are identical.
TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       BrowserType_DefinitionsMatch) {
  EXPECT_EQ(::BROWSER_UNKNOWN,            omaha::BROWSER_UNKNOWN);
  EXPECT_EQ(::BROWSER_DEFAULT,            omaha::BROWSER_DEFAULT);
  EXPECT_EQ(::BROWSER_INTERNET_EXPLORER,  omaha::BROWSER_IE);
  EXPECT_EQ(::BROWSER_FIREFOX,            omaha::BROWSER_FIREFOX);
  EXPECT_EQ(::BROWSER_CHROME,             omaha::BROWSER_CHROME);

  EXPECT_EQ(::BROWSER_CHROME + 1, omaha::BROWSER_MAX)
      << _T("A browser has been added without updating test and/or the IDL");
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest, CurrentState) {
  EXPECT_EQ(1,  STATE_INIT);
  EXPECT_EQ(2,  STATE_WAITING_TO_CHECK_FOR_UPDATE);
  EXPECT_EQ(3,  STATE_CHECKING_FOR_UPDATE);
  EXPECT_EQ(4,  STATE_UPDATE_AVAILABLE);
  EXPECT_EQ(5,  STATE_WAITING_TO_DOWNLOAD);
  EXPECT_EQ(6,  STATE_RETRYING_DOWNLOAD);
  EXPECT_EQ(7,  STATE_DOWNLOADING);
  EXPECT_EQ(8,  STATE_DOWNLOAD_COMPLETE);
  EXPECT_EQ(9,  STATE_EXTRACTING);
  EXPECT_EQ(10, STATE_APPLYING_DIFFERENTIAL_PATCH);
  EXPECT_EQ(11, STATE_READY_TO_INSTALL);
  EXPECT_EQ(12, STATE_WAITING_TO_INSTALL);
  EXPECT_EQ(13, STATE_INSTALLING);
  EXPECT_EQ(14, STATE_INSTALL_COMPLETE);
  EXPECT_EQ(15, STATE_PAUSED);
  EXPECT_EQ(16, STATE_NO_UPDATE);
  EXPECT_EQ(17, STATE_ERROR);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest, InstallPriority) {
  EXPECT_EQ(0,  INSTALL_PRIORITY_LOW);
  EXPECT_EQ(10, INSTALL_PRIORITY_HIGH);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest, PostInstallAction) {
  EXPECT_EQ(0, POST_INSTALL_ACTION_DEFAULT);
  EXPECT_EQ(1, POST_INSTALL_ACTION_EXIT_SILENTLY);
  EXPECT_EQ(2, POST_INSTALL_ACTION_LAUNCH_COMMAND);
  EXPECT_EQ(3, POST_INSTALL_ACTION_EXIT_SILENTLY_ON_LAUNCH_COMMAND);
  EXPECT_EQ(4, POST_INSTALL_ACTION_RESTART_BROWSER);
  EXPECT_EQ(5, POST_INSTALL_ACTION_RESTART_ALL_BROWSERS);
  EXPECT_EQ(6, POST_INSTALL_ACTION_REBOOT);
}

//
// Omaha 3 COM Interfaces.
//

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, TypeLib) {
  EXPECT_ID_EQ(_T("{9b4380f4-4748-446b-ae53-b1c983e8f268}"),
               LIBID_GoogleUpdate3Lib);

  EXPECT_SUCCEEDED(GetDocumentation(-1));
  EXPECT_STREQ(_T("GoogleUpdate3Lib"), item_name_);
  EXPECT_GU_STREQ(_T("Google Update 3.0 Type Library"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IGoogleUpdate3) {
  // TODO(omaha): Test uuid constants after extracting from IDLs.
  EXPECT_ID_EQ(_T("{d768de81-cf6b-4e24-9312-2cd6efc84ec1}"),
               __uuidof(IGoogleUpdate3));

  EXPECT_SUCCEEDED(GetDocumentation(0));
  EXPECT_STREQ(_T("IGoogleUpdate3"), item_name_);
  EXPECT_STREQ(_T("IGoogleUpdate3 Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

// The IAppBundle interface name does not change for non-Google builds, but the
// ID must. The same is true for many of the interfaces.
TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IAppBundle) {
  EXPECT_ID_EQ(_T("{5a779105-eff9-46f4-addf-e007c9dd5210}"),
               __uuidof(IAppBundle));

  EXPECT_SUCCEEDED(GetDocumentation(1));
  EXPECT_STREQ(_T("IAppBundle"), item_name_);
  EXPECT_STREQ(_T("IAppBundle Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

// This appears in the typelib for unknown reasons.
TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, ULONG_PTR) {
  EXPECT_SUCCEEDED(GetDocumentation(2));
  EXPECT_STREQ(_T("ULONG_PTR"), item_name_);
  EXPECT_TRUE(!item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IApp) {
  EXPECT_ID_EQ(_T("{394ad438-459e-41c6-9810-5457a87a940e}"),
               __uuidof(IApp));

  EXPECT_SUCCEEDED(GetDocumentation(3));
  EXPECT_STREQ(_T("IApp"), item_name_);
  EXPECT_STREQ(_T("IApp Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IAppVersion) {
  EXPECT_ID_EQ(_T("{1460b212-d5d1-49e6-b92a-5f95f5a57a59}"),
               __uuidof(IAppVersion));

  EXPECT_SUCCEEDED(GetDocumentation(4));
  EXPECT_STREQ(_T("IAppVersion"), item_name_);
  EXPECT_STREQ(_T("IAppVersion Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IPackage) {
  EXPECT_ID_EQ(_T("{3ca7c737-18ac-4552-a4bc-871db39e86cd}"),
               __uuidof(IPackage));

  EXPECT_SUCCEEDED(GetDocumentation(5));
  EXPECT_STREQ(_T("IPackage"), item_name_);
  EXPECT_STREQ(_T("IPackage Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, ICurrentState) {
  EXPECT_ID_EQ(_T("{8ce9c2c0-986e-468c-a797-9b980e8bab7a}"),
               __uuidof(ICurrentState));

  EXPECT_SUCCEEDED(GetDocumentation(6));
  EXPECT_STREQ(_T("ICurrentState"), item_name_);
  EXPECT_STREQ(_T("ICurrentState Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

// Not in the TypeLib because it derives from IUnknown.
TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       IRegistrationUpdateHook) {
  EXPECT_ID_EQ(_T("{1c75c7be-2b6f-4bf3-bc88-1ffae024d573}"),
               __uuidof(IRegistrationUpdateHook));
}

// Not in the TypeLib because it derives from IUnknown.
TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest, ICoCreateAsync) {
  EXPECT_ID_EQ(_T("{ce9c85e2-3124-451a-8bfb-5e5ff8c5e003}"),
               __uuidof(ICoCreateAsync));
}

// Not in the TypeLib because it derives from IUnknown.
TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest, ICredentialDialog) {
  EXPECT_ID_EQ(_T("{d2dbe58f-1d48-4f12-a2d6-782ceb617ea1}"),
               __uuidof(ICredentialDialog));
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IGoogleUpdate3Web) {
  EXPECT_ID_EQ(_T("{b4a2f745-ab70-4721-8ebc-e379e444fa7c}"),
               __uuidof(IGoogleUpdate3Web));

  EXPECT_SUCCEEDED(GetDocumentation(7));
  EXPECT_STREQ(_T("IGoogleUpdate3Web"), item_name_);
  EXPECT_STREQ(_T("IGoogleUpdate3Web Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

// Not in the TypeLib because it derives from IUnknown.
TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       IGoogleUpdate3WebSecurity) {
  EXPECT_ID_EQ(_T("{37ccdc88-d302-42ca-9ef7-100484a457ed}"),
               __uuidof(IGoogleUpdate3WebSecurity));
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IAppBundleWeb) {
  EXPECT_ID_EQ(_T("{39d9ea1f-b696-411d-8a22-158ad8067fad}"),
               __uuidof(IAppBundleWeb));

  EXPECT_SUCCEEDED(GetDocumentation(8));
  EXPECT_STREQ(_T("IAppBundleWeb"), item_name_);
  EXPECT_STREQ(_T("IAppBundleWeb Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IAppWeb) {
  EXPECT_ID_EQ(_T("{e14b3553-a8bf-432e-9147-208162db02fa}"),
               __uuidof(IAppWeb));

  EXPECT_SUCCEEDED(GetDocumentation(9));
  EXPECT_STREQ(_T("IAppWeb"), item_name_);
  EXPECT_STREQ(_T("IAppWeb Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, IAppVersionWeb) {
  EXPECT_ID_EQ(_T("{94f470b7-fee4-455a-a575-2c2f243a0b85}"),
               __uuidof(IAppVersionWeb));

  EXPECT_SUCCEEDED(GetDocumentation(10));
  EXPECT_STREQ(_T("IAppVersionWeb"), item_name_);
  EXPECT_STREQ(_T("IAppVersionWeb Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, ICoCreateAsyncStatus) {
  EXPECT_ID_EQ(_T("{64192ce2-8c6d-488d-8401-dd41b61fb23f}"),
               __uuidof(ICoCreateAsyncStatus));

  EXPECT_SUCCEEDED(GetDocumentation(11));
  EXPECT_STREQ(_T("ICoCreateAsyncStatus"), item_name_);
  EXPECT_STREQ(_T("ICoCreateAsyncStatus Interface"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleUpdate3UserClass) {
  EXPECT_ID_EQ(_T("{5b98b77c-abfb-4aa1-ab5a-f4d20dae28ea}"),
               __uuidof(GoogleUpdate3UserClass));

  EXPECT_SUCCEEDED(GetDocumentation(12));
  EXPECT_STREQ(_T("GoogleUpdate3UserClass"), item_name_);
  EXPECT_STREQ(_T("GoogleUpdate3 Class for per-user applications"),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleUpdate3ServiceClass) {
  EXPECT_ID_EQ(_T("{64aa5955-9f45-4735-a6b4-3618dc7dec0a}"),
               __uuidof(GoogleUpdate3ServiceClass));

  EXPECT_SUCCEEDED(GetDocumentation(13));
  EXPECT_STREQ(_T("GoogleUpdate3ServiceClass"), item_name_);
  EXPECT_STREQ(_T("GoogleUpdate3 Service Class for machine applications"),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleUpdate3WebUserClass) {
  EXPECT_ID_EQ(_T("{a3de3ca6-117c-4e27-aeaa-4cc30d274464}"),
               __uuidof(GoogleUpdate3WebUserClass));

  EXPECT_SUCCEEDED(GetDocumentation(14));
  EXPECT_STREQ(_T("GoogleUpdate3WebUserClass"), item_name_);
  EXPECT_STREQ(_T("GoogleUpdate3Web for user applications"),
                  item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleUpdate3WebMachineClass) {
  EXPECT_ID_EQ(_T("{20bb664b-892a-46d0-adb5-a95226c6ccde}"),
               __uuidof(GoogleUpdate3WebMachineClass));

  EXPECT_SUCCEEDED(GetDocumentation(15));
  EXPECT_STREQ(_T("GoogleUpdate3WebMachineClass"), item_name_);
  EXPECT_STREQ(
      _T("Pass-through broker for the GoogleUpdate3WebServiceClass"),
      item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleUpdate3WebServiceClass) {
  EXPECT_ID_EQ(_T("{e84cb028-8b07-498c-b99b-dca01b3d70c3}"),
               __uuidof(GoogleUpdate3WebServiceClass));

  EXPECT_SUCCEEDED(GetDocumentation(16));
  EXPECT_STREQ(_T("GoogleUpdate3WebServiceClass"), item_name_);
  EXPECT_STREQ(_T("GoogleUpdate3Web"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleUpdate3WebMachineFallbackClass) {
  EXPECT_ID_EQ(_T("{1e94c95a-dde7-4c32-ac7a-79942f7fe69f}"),
               __uuidof(GoogleUpdate3WebMachineFallbackClass));

  EXPECT_SUCCEEDED(GetDocumentation(17));
  EXPECT_STREQ(_T("GoogleUpdate3WebMachineFallbackClass"), item_name_);
  EXPECT_STREQ(L"Fallback mechanism if GoogleUpdate3WebServiceClass fails",
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              CurrentStateUserClass) {
  EXPECT_ID_EQ(_T("{2b218e8d-3fc5-43aa-8b87-57e1db959e6e}"),
               __uuidof(CurrentStateUserClass));

  EXPECT_SUCCEEDED(GetDocumentation(18));
  EXPECT_STREQ(_T("CurrentStateUserClass"), item_name_);
  EXPECT_STREQ(_T("CurrentStateUserClass"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              CurrentStateMachineClass) {
  EXPECT_ID_EQ(_T("{3e813b0f-2cda-4eb3-bd29-0958d8fab6c8}"),
               __uuidof(CurrentStateMachineClass));

  EXPECT_SUCCEEDED(GetDocumentation(19));
  EXPECT_STREQ(_T("CurrentStateMachineClass"), item_name_);
  EXPECT_STREQ(_T("CurrentStateMachineClass"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              CoCreateAsyncClass) {
  EXPECT_ID_EQ(_T("{d9fd43a8-1b96-4af8-95bc-39dad98f8c14}"),
               __uuidof(CoCreateAsyncClass));

  EXPECT_SUCCEEDED(GetDocumentation(20));
  EXPECT_STREQ(_T("CoCreateAsyncClass"), item_name_);
  EXPECT_STREQ(_T("CoCreateAsyncClass"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              CredentialDialogUserClass) {
  EXPECT_ID_EQ(_T("{ee783eb8-25ab-4c1f-b233-06ca1a154e97}"),
               __uuidof(CredentialDialogUserClass));

  EXPECT_SUCCEEDED(GetDocumentation(21));
  EXPECT_STREQ(_T("CredentialDialogUserClass"), item_name_);
  EXPECT_STREQ(_T("CredentialDialogUserClass"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              CredentialDialogMachineClass) {
  EXPECT_ID_EQ(_T("{9fc5d2ce-a510-40d7-94c2-c8f050a9119d}"),
               __uuidof(CredentialDialogMachineClass));

  EXPECT_SUCCEEDED(GetDocumentation(22));
  EXPECT_STREQ(_T("CredentialDialogMachineClass"), item_name_);
  EXPECT_STREQ(_T("CredentialDialogMachineClass"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleComProxyMachineClass) {
  EXPECT_SUCCEEDED(GetDocumentation(23));
  EXPECT_STREQ(_T("GoogleComProxyMachineClass"), item_name_);
  EXPECT_STREQ(_T("GoogleComProxyMachineClass"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleComProxyUserClass) {
  EXPECT_SUCCEEDED(GetDocumentation(24));
  EXPECT_STREQ(_T("GoogleComProxyUserClass"), item_name_);
  EXPECT_STREQ(_T("GoogleComProxyUserClass"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              ProcessLauncherClass) {
  EXPECT_ID_EQ(_T("{7819c81b-06aa-420e-ae2d-739641b1e56b}"),
               __uuidof(ProcessLauncherClass));

  EXPECT_SUCCEEDED(GetDocumentation(25));
  EXPECT_STREQ(_T("ProcessLauncherClass"), item_name_);
  EXPECT_STREQ(_T("ProcessLauncherClass Class"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              OneClickUserProcessLauncherClass) {
  EXPECT_ID_EQ(_T("{f087530c-d068-40fe-b0e9-f125b49726ec}"),
               __uuidof(OneClickUserProcessLauncherClass));

  EXPECT_SUCCEEDED(GetDocumentation(26));
  EXPECT_STREQ(_T("OneClickUserProcessLauncherClass"), item_name_);
  EXPECT_STREQ(_T("OneClickUserProcessLauncherClass Class"),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              IOneClickProcessLauncher) {
  EXPECT_ID_EQ(_T("{49d8a6fe-a91e-4480-b51f-becea4469280}"),
               __uuidof(IOneClickProcessLauncher));

  EXPECT_SUCCEEDED(GetDocumentation(27));
  EXPECT_STREQ(_T("IOneClickProcessLauncher"), item_name_);
  EXPECT_STREQ(_T("Google Update IOneClickProcessLauncher Interface"),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              OneClickMachineProcessLauncherClass) {
  EXPECT_ID_EQ(_T("{1af4b64d-96c8-4ea7-8ad6-0e75be985fb8}"),
               __uuidof(OneClickMachineProcessLauncherClass));

  EXPECT_SUCCEEDED(GetDocumentation(28));
  EXPECT_STREQ(_T("OneClickMachineProcessLauncherClass"), item_name_);
  EXPECT_STREQ(_T("OneClickMachineProcessLauncherClass Class"),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              OnDemandUserAppsClass) {
  EXPECT_ID_EQ(_T("{9fe785b6-a46d-44ed-a9c7-3695696025aa}"),
               __uuidof(OnDemandUserAppsClass));

  EXPECT_SUCCEEDED(GetDocumentation(29));
  EXPECT_STREQ(_T("OnDemandUserAppsClass"), item_name_);
  EXPECT_STREQ(_T("OnDemand updates for per-user applications."),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              OnDemandMachineAppsClass) {
  EXPECT_ID_EQ(_T("{f49d8b15-51e3-459d-a03d-23472af4e77d}"),
               __uuidof(OnDemandMachineAppsClass));

  EXPECT_SUCCEEDED(GetDocumentation(30));
  EXPECT_STREQ(_T("OnDemandMachineAppsClass"), item_name_);
  EXPECT_STREQ(_T("OnDemand pass-through broker for machine applications."),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              OnDemandMachineAppsServiceClass) {
  EXPECT_ID_EQ(_T("{21b903cf-a4ed-4d92-91b0-4d63cd0dad1e}"),
               __uuidof(OnDemandMachineAppsServiceClass));

  EXPECT_SUCCEEDED(GetDocumentation(31));
  EXPECT_STREQ(_T("OnDemandMachineAppsServiceClass"), item_name_);
  EXPECT_STREQ(_T("OnDemand updates for per-machine applications."),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              OnDemandMachineAppsFallbackClass) {
  EXPECT_ID_EQ(_T("{cde9ac86-25da-47a1-aa7a-c2c98f2a4213}"),
               __uuidof(OnDemandMachineAppsFallbackClass));

  EXPECT_SUCCEEDED(GetDocumentation(32));
  EXPECT_STREQ(_T("OnDemandMachineAppsFallbackClass"), item_name_);
  EXPECT_STREQ(_T("Fallback for if OnDemandMachineAppsServiceClass fails."),
               item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleUpdateCoreClass) {
  EXPECT_ID_EQ(_T("{73cde2da-150e-4ce2-ac97-93955ce39c82}"),
               __uuidof(GoogleUpdateCoreClass));

  EXPECT_SUCCEEDED(GetDocumentation(33));
  EXPECT_STREQ(_T("GoogleUpdateCoreClass"), item_name_);
  EXPECT_STREQ(_T("GoogleUpdateCore Class"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

TEST_GU_INT_F(NinjaDeployCustomizationGoopdateComInterfaceTest,
              GoogleUpdateCoreMachineClass) {
  EXPECT_ID_EQ(_T("{b41f8fc7-eae7-4ff1-af7c-21c8a18cbb08}"),
               __uuidof(GoogleUpdateCoreMachineClass));

  EXPECT_SUCCEEDED(GetDocumentation(34));
  EXPECT_STREQ(_T("GoogleUpdateCoreMachineClass"), item_name_);
  EXPECT_STREQ(_T("GoogleUpdateCore Machine Class"), item_doc_string_);
  EXPECT_EQ(0, help_context_);
  EXPECT_TRUE(!help_file_);
}

// Verifies there are no new interfaces in the TypeLib.
TEST_F(NinjaDeployCustomizationGoopdateComInterfaceTest, VerifyNoNewInterfaces) {
  EXPECT_EQ(TYPE_E_ELEMENTNOTFOUND, GetDocumentation(35))
      << _T("A new interface may have been added. If so, roll ")
      << _T("PROXY_CLSID_IS_MACHINE/USER and GoogleComProxyMachine/UserClass, ")
      << _T("add the interface to kIIDsToRegister, and add test(s) for new ")
      << _T("interface(s).");
}

//
// Omaha 2 COM Interfaces.
//
// TODO(omaha): We should make it so open source versions do not need these
// legacy interfaces.

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       IBrowserHttpRequest2) {
  EXPECT_ID_EQ(_T("{1de375df-f797-4a87-8d19-8a5c193d76b1}"),
               __uuidof(IBrowserHttpRequest2));
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       IProcessLauncher) {
  EXPECT_ID_EQ(_T("{1884876c-7278-4aaa-bf05-4112d1b2776a}"),
               __uuidof(IProcessLauncher));
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       IProgressWndEvents) {
  EXPECT_ID_EQ(_T("{d23f9db4-5887-440a-925c-088d1199e045}"),
               __uuidof(IProgressWndEvents));
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       IJobObserver) {
  EXPECT_ID_EQ(_T("{892bb63e-d9dd-4863-9a86-ab17ef611ea7}"),
               __uuidof(IJobObserver));
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       IGoogleUpdate) {
  EXPECT_ID_EQ(_T("{0517eabd-aff3-4f95-8cc2-477fd3d71e30}"),
               __uuidof(IGoogleUpdate));
}

TEST_F(NinjaDeployCustomizationGoopdateComInterfaceNoTypeLibTest,
       IGoogleUpdateCore) {
  EXPECT_ID_EQ(_T("{e3ff0986-de5e-4973-92f8-52bde1057612}"),
               __uuidof(IGoogleUpdateCore));
}
