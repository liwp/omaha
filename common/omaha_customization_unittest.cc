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

#include <tchar.h>
#include "omaha/base/const_addresses.h"
#include "omaha/base/const_config.h"
#include "omaha/base/const_debug.h"
#include "omaha/base/const_object_names.h"
#include "omaha/base/constants.h"
#include "omaha/base/logging.h"
#include "omaha/base/process.h"
#include "omaha/base/utils.h"
#include "omaha/common/config_manager.h"
#include "omaha/common/const_goopdate.h"
#include "omaha/common/const_group_policy.h"
#include "omaha/common/omaha_customization_proxy_clsid.h"
#include "omaha/testing/omaha_customization_test.h"

// TODO(omaha): Make use of EXPECT_GU_STREQ, etc.

namespace omaha {

TEST(OmahaCustomizationTest, Constants_BuildFiles) {
  // Primary main.scons values.

  // TODO(omaha): Most of these tests are of extremely questionable
  // value, as they're just checking that certain #defines exist and
  // haven't changed.  But, unanticipated changes to most of these
  // would cause build breaks anyways!  Consider deleting them.
#ifdef GOOGLE_UPDATE_BUILD
  EXPECT_STREQ("Google Inc.", FULL_COMPANY_NAME_ANSI);
  EXPECT_STREQ("Google", SHORT_COMPANY_NAME_ANSI);
  EXPECT_STREQ("Update", PRODUCT_NAME_ANSI);

  EXPECT_STREQ("google", COMPANY_DOMAIN_BASE_ANSI);
  EXPECT_STREQ("google.com", COMPANY_DOMAIN_ANSI);

  EXPECT_STREQ("Google Update", OMAHA_APP_NAME_ANSI);
#endif  // GOOGLE_UPDATE_BUILD

  EXPECT_STREQ("goopdate", MAIN_DLL_BASE_NAME_ANSI);

  const GUID kActualProxyClsidIsMachineGuid = PROXY_CLSID_IS_MACHINE;
  EXPECT_TRUE(::IsEqualGUID(kProxyClsidIsMachineGuid,
                            kActualProxyClsidIsMachineGuid));

  const GUID kActualProxyClsidIsUserGuid = PROXY_CLSID_IS_USER;
  EXPECT_TRUE(::IsEqualGUID(kProxyClsidIsUserGuid,
                            kActualProxyClsidIsUserGuid));

  // VERSION file values. Only the relatively stable ones are tested.
  // The versions may or may not match in non-Google Update builds.
#ifdef GOOGLE_UPDATE_BUILD
  EXPECT_STREQ("9", ONECLICK_PLUGIN_VERSION_ANSI);
  // TODO(omaha): Change the name to ANSI.
  EXPECT_STREQ("3", UPDATE_PLUGIN_VERSION_ANSI);
#else
  std::wcout << _T("Did not test version values.") << std::endl;
#endif

  // Primary omaha_version_utils values.
  EXPECT_STREQ(_T("npNinjaDeployOneClick"), ONECLICK_PLUGIN_NAME);
  EXPECT_STREQ(_T("npNinjaDeployUpdate"), UPDATE_PLUGIN_NAME);
  EXPECT_STREQ(_T("GoopdateBho"), BHO_NAME);

  // Filenames from omaha_version_utils.
  EXPECT_STREQ(
      _T("npNinjaDeployOneClick") _T(ONECLICK_PLUGIN_VERSION_ANSI) _T(".dll"),
      ONECLICK_PLUGIN_FILENAME);
  EXPECT_STREQ(_T("npNinjaDeployUpdate") _T(UPDATE_PLUGIN_VERSION_ANSI) _T(".dll"),
               UPDATE_PLUGIN_FILENAME);
  EXPECT_STREQ(_T("GoopdateBho.dll"), BHO_FILENAME);
}

TEST(OmahaCustomizationTest, Constants_Names) {
  // Company and product names.

  // TODO(omaha): Most of these tests are of extremely questionable
  // value, as they're just checking that certain #defines exist and
  // haven't changed.  But, unanticipated changes to most of these
  // would cause build breaks anyways!  Consider deleting them.
#ifdef GOOGLE_UPDATE_BUILD
  EXPECT_STREQ(_T("Google Inc."), kFullCompanyName);
  EXPECT_STREQ(_T("Google"), SHORT_COMPANY_NAME);
  EXPECT_STREQ(_T("Google"), kShortCompanyName);
  EXPECT_STREQ(_T("Update"), PRODUCT_NAME);

  EXPECT_STREQ(_T("google.com"), COMPANY_DOMAIN);

  // Full app name.
  EXPECT_STREQ(_T("Google Update"), kAppName);

  // Identifiers.
  EXPECT_STREQ(_T("Google"), COMPANY_NAME_IDENTIFIER);
  EXPECT_STREQ(_T("Update"), PRODUCT_NAME_IDENTIFIER);
  EXPECT_STREQ(_T("GoogleUpdate"), APP_NAME_IDENTIFIER);

  // Other values based on the app name.
  EXPECT_STREQ(_T("_Google_Update_"), kLockPrefix);
#endif  // GOOGLE_UPDATE_BUILD

  // Filename bases
  EXPECT_STREQ(_T("NinjaDeployUpdate"), MAIN_EXE_BASE_NAME);
  EXPECT_STREQ(_T("goopdate"), MAIN_DLL_BASE_NAME);
}

TEST(OmahaCustomizationTest, Constants_Filenames) {
  EXPECT_STREQ(_T("NinjaDeployUpdate.exe"), kOmahaShellFileName);
  EXPECT_STREQ(_T("NinjaDeployCrashHandler.exe"), kCrashHandlerFileName);
  EXPECT_STREQ(_T("goopdate.dll"), kOmahaDllName);
  EXPECT_STREQ(_T("goopdateres_%s.dll"), kOmahaResourceDllNameFormat);
  EXPECT_STREQ(_T("NinjaDeployUpdateBroker.exe"), kOmahaBrokerFileName);
  EXPECT_STREQ(_T("NinjaDeployUpdateOnDemand.exe"), kOmahaOnDemandFileName);
  EXPECT_STREQ(_T("psmachine.dll"), kPSFileNameMachine);
  EXPECT_STREQ(_T("psuser.dll"), kPSFileNameUser);
}

TEST(OmahaCustomizationTest, Constants_Certificate) {
  EXPECT_STREQ(_T("Google Inc"), kCertificateSubjectName);
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_String) {
  EXPECT_STREQ(_T("{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), GOOPDATE_APP_ID);
  EXPECT_STREQ(_T("{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"),
               kGoogleUpdateAppId);
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_GUID) {
  const GUID kExpectedGoogleUpdateGuid =
      {0x5CB309C8, 0x48AD, 0x4C7A,
       {0x83, 0x79, 0x15, 0x69, 0x6D, 0xF9, 0xD3, 0x1D}};
  EXPECT_TRUE(::IsEqualGUID(kExpectedGoogleUpdateGuid, kGoopdateGuid));
  EXPECT_STREQ(_T("{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"),
               GuidToString(kGoopdateGuid));
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_GUIDAndStringMatch) {
  EXPECT_STREQ(kGoogleUpdateAppId, GuidToString(kGoopdateGuid));
}

TEST(OmahaCustomizationTest, Constants_Directories) {
  EXPECT_STREQ(_T("Offline"), OFFLINE_DIR_NAME);
  EXPECT_GU_STREQ(_T("Google"), OMAHA_REL_COMPANY_DIR);
  EXPECT_GU_STREQ(_T("Google\\CrashReports"), OMAHA_REL_CRASH_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update"), OMAHA_REL_GOOPDATE_INSTALL_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update\\Log"), OMAHA_REL_LOG_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update\\Offline"),
                  OMAHA_REL_OFFLINE_STORAGE_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update\\Download"),
                  OMAHA_REL_DOWNLOAD_STORAGE_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update\\Install"),
                  OMAHA_REL_INSTALL_WORKING_DIR);
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys_NotCustomized) {
  EXPECT_STREQ(_T("HKLM"), MACHINE_KEY_NAME);
  EXPECT_STREQ(_T("HKLM\\"), MACHINE_KEY);
  EXPECT_STREQ(_T("HKCU"), USER_KEY_NAME);
  EXPECT_STREQ(_T("HKCU\\"), USER_KEY);
  EXPECT_STREQ(_T("HKU\\"), USERS_KEY);
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys) {
  EXPECT_GU_STREQ(_T("Software\\Google\\"), COMPANY_MAIN_KEY);
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\"), GOOPDATE_MAIN_KEY);
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\Clients\\"), GOOPDATE_REG_RELATIVE_CLIENTS);  // NOLINT
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\ClientState\\"), GOOPDATE_REG_RELATIVE_CLIENT_STATE);  // NOLINT
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\ClientStateMedium\\"), GOOPDATE_REG_RELATIVE_CLIENT_STATE_MEDIUM);  // NOLINT
  EXPECT_GU_STREQ(_T("Software\\Policies\\Google\\"), COMPANY_POLICIES_MAIN_KEY);
  EXPECT_GU_STREQ(_T("Software\\Policies\\Google\\Update\\"), GOOPDATE_POLICIES_RELATIVE);  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\"), USER_REG_GOOGLE);
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\"), USER_REG_UPDATE);
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\"), USER_REG_CLIENTS);  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), USER_REG_CLIENTS_GOOPDATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\"), USER_REG_CLIENT_STATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), USER_REG_CLIENT_STATE_GOOPDATE);  // NOLINT

  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\"), MACHINE_REG_GOOGLE);
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\"), MACHINE_REG_UPDATE);
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\"), MACHINE_REG_CLIENTS);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), MACHINE_REG_CLIENTS_GOOPDATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\"), MACHINE_REG_CLIENT_STATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), MACHINE_REG_CLIENT_STATE_GOOPDATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientStateMedium\\"), MACHINE_REG_CLIENT_STATE_MEDIUM);  // NOLINT

  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\UpdateDev\\"), MACHINE_REG_UPDATE_DEV);  // NOLINT
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys_GroupPolicy) {
  EXPECT_GU_STREQ(_T("Software\\Policies\\Google\\Update\\"), GOOPDATE_POLICIES_RELATIVE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Policies\\Google\\Update\\"), kRegKeyGoopdateGroupPolicy);  // NOLINT
}

TEST(OmahaCustomizationTest, Constants_RegistryValues) {
  EXPECT_GU_STREQ(_T("Google Update"), kRunValueName);
}

TEST(OmahaCustomizationTest, Constants_MsiMsp) {
  EXPECT_STREQ(_T("NinjaDeployUpdateHelper.msi"), kHelperInstallerName);
  EXPECT_STREQ(_T("{A92DAB39-4E2C-4304-9AB6-BC44E68B55E2}"),
               kHelperInstallerProductGuid);
  EXPECT_STREQ(_T("NinjaDeployUpdateHelperPatch.msp"), kHelperPatchName);
  EXPECT_STREQ(_T("{E0D0D2C9-5836-4023-AB1D-54EC3B90AD03}"), kHelperPatchGuid);
}

TEST(OmahaCustomizationTest, Constants_CompatibleShellVersions) {
  EXPECT_EQ(2, arraysize(kCompatibleOlderShellVersions));
  EXPECT_EQ(0x0001000200830007, kCompatibleOlderShellVersions[0]);
  EXPECT_EQ(0x0001000200B70009, kCompatibleOlderShellVersions[1]);
}

TEST(OmahaCustomizationTest, Constants_BrandCode) {
  EXPECT_STREQ(_T("GGLS"), kDefaultGoogleUpdateBrandCode);
}

TEST(OmahaCustomizationTest, Constants_Addresses) {
  EXPECT_STREQ(_T("www.google.com"), kGoogleHttpServer);
  EXPECT_STREQ(_T("www.google.com"), kGoopdateServer);
  EXPECT_STREQ(_T("https://www.google.com/update2"), kUrlUpdateCheck);
  EXPECT_STREQ(_T("http://www.google.com/update2"), kUrlPing);
  EXPECT_STREQ(_T("http://www.google.com/report"), kUrlCrashReport);
  EXPECT_STREQ(_T("http://www.google.com/support/installer/?"), kUrlMoreInfo);
  EXPECT_STREQ(_T("http://www.google.com/check2"),
               kUrlCodeRedCheck);
  EXPECT_STREQ(_T("http://www.google.com/usagestats"),
               kUrlUsageStatsReport);
}

TEST(OmahaCustomizationTest, Constants_Config) {
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\Shared"), kCiRegKeyShared);
}

TEST(OmahaCustomizationTest, Constants_Debug) {
  EXPECT_GU_STREQ(_T("GoogleUpdate-debug"), kCiDebugDirectory);
}

TEST(OmahaCustomizationTest, Constants_Logging) {
  EXPECT_STREQ(_T("NinjaDeployUpdate.ini"), kLogConfigFileName);
  EXPECT_STREQ(_T("NinjaDeployUpdate.log"), kDefaultLogFileName);
}

// These should not change during customization.
TEST(OmahaCustomizationTest, Constants_ObjectNames_Prefixes) {
  EXPECT_GU_STREQ(_T("Global\\G"), kGlobalPrefix);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_Pipes) {
  EXPECT_GU_STREQ(_T("\\\\.\\pipe\\GoogleCrashServices"), kCrashPipeNamePrefix);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_MutexesAndEvents) {
  EXPECT_STREQ(_T("{A9A86B93-B54E-4570-BE89-42418507707B}"), kSetupMutex);
  EXPECT_STREQ(_T("{A0C1F415-D2CE-4ddc-9B48-14E56FD55162}"), kShutdownEvent);
  EXPECT_STREQ(_T("{B5665124-2B19-40e2-A7BC-B44321E72C4B}"),
               kCoreSingleInstance);
  EXPECT_STREQ(_T("{C4F406E5-F024-4e3f-89A7-D5AB7663C3CD}"),
               kCrashHandlerSingleInstance);
  EXPECT_STREQ(_T("{D0BB2EF1-C183-4cdb-B218-040922092869}"),
               kUpdateAppsSingleInstance);
  EXPECT_STREQ(_T("%s-{F707E94F-D66B-4525-AD84-B1DA87D6A971}"),
               kInstallAppSingleInstance);
  EXPECT_STREQ(_T("{0A175FBE-AEEC-4fea-855A-2AA549A88846}"),
               kInstallManagerSerializer);
  EXPECT_STREQ(_T("{C68009EA-1163-4498-8E93-D5C4E317D8CE}"),
               kMetricsSerializer);
  EXPECT_STREQ(_T("{0E900C7B-04B0-47f9-81B0-F8D94F2DF01B}"),
               kNetworkConfigLock);
  EXPECT_STREQ(_T("{66CC0160-ABB3-4066-AE47-1CA6AD5065C8}"),
               kRegistryAccessMutex);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_SharedMemory) {
  EXPECT_GU_STREQ(_T("Global\\GoogleUpdate3"),
                  kGoogleUpdate3SharedMemoryName);
  EXPECT_GU_STREQ(_T("Global\\GoogleUpdateCore"),
                  kGoogleUpdateCoreSharedMemoryName);
}

TEST(OmahaCustomizationTest, Constants_Services) {
  EXPECT_GU_STREQ(_T("gupdate_service_name"), kRegValueServiceName);
  EXPECT_GU_STREQ(_T("gupdatem_service_name"), kRegValueMediumServiceName);
  EXPECT_GU_STREQ(_T("gupdate_task_name_c"), kRegValueTaskNameC);
  EXPECT_GU_STREQ(_T("gupdate_task_name_ua"), kRegValueTaskNameUA);

  EXPECT_GU_STREQ(_T("gupdate"), kServicePrefix);
  EXPECT_GU_STREQ(_T("gupdatem"), kMediumServicePrefix);

  EXPECT_STREQ(_T("NinjaDeployUpdate.exe"), kServiceFileName);
}

TEST(OmahaCustomizationTest, Constants_ScheduledTasks) {
  EXPECT_GU_STREQ(_T("GoogleUpdateTaskUser"), kScheduledTaskNameUserPrefix);
  EXPECT_GU_STREQ(_T("GoogleUpdateTaskMachine"), kScheduledTaskNameMachinePrefix);
}

TEST(OmahaCustomizationTest, Constants_Plugins) {
  EXPECT_GU_STREQ(_T("Google.OneClickCtrl.") _T(ONECLICK_PLUGIN_VERSION_ANSI),
                  kOneClickProgId);
  EXPECT_STREQ(
      "application/x-vnd.google.oneclickctrl." ONECLICK_PLUGIN_VERSION_ANSI,
      kOneClickPluginMimeTypeAnsi);
}

TEST(OmahaCustomizationTest, Constants_HostCheck) {
  EXPECT_EQ(4, arraysize(kSiteLockPatternStrings));
  EXPECT_STREQ(_T("^(gears)|(mail)|(tools)|(www)|(desktop)|(pack)\\.google\\.com$"), kSiteLockPatternStrings[0]);  // NOLINT
  EXPECT_STREQ(_T("^www\\.google\\.(ad)|(bg)|(ca)|(cn)|(cz)|(de)|(es)|(fi)|(fr)|(gr)|(hr)|(hu)|(it)|(ki)|(kr)|(lt)|(lv)|(nl)|(no)|(pl)|(pt)|(ro)|(ru)|(sk)|(sg)|(sl)|(sr)|(vn)$"), kSiteLockPatternStrings[1]);  // NOLINT
  EXPECT_STREQ(_T("^www\\.google\\.co\\.(hu)|(id)|(il)|(it)|(jp)|(kr)|(th)|(uk)$"), kSiteLockPatternStrings[2]);  // NOLINT
  EXPECT_STREQ(_T("^www\\.google\\.com\\.(ar)|(au)|(br)|(cn)|(et)|(gr)|(hr)|(ki)|(lv)|(om)|(pl)|(pt)|(ru)|(sg)|(sv)|(tr)|(vn)$"), kSiteLockPatternStrings[3]);  // NOLINT
}

//
// ConfigManager keys.
//

TEST(OmahaCustomizationTest, ConfigManager_RegistryKeys) {
  const ConfigManager& cm = *ConfigManager::Instance();

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\"), cm.user_registry_clients());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\"), cm.machine_registry_clients());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\"), cm.registry_clients(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\"), cm.registry_clients(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), cm.user_registry_clients_goopdate());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), cm.machine_registry_clients_goopdate());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), cm.registry_clients_goopdate(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), cm.registry_clients_goopdate(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\"), cm.user_registry_client_state());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\"), cm.machine_registry_client_state());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\"), cm.registry_client_state(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\"), cm.registry_client_state(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), cm.user_registry_client_state_goopdate());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), cm.machine_registry_client_state_goopdate());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), cm.registry_client_state_goopdate(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\{5CB309C8-48AD-4C7A-8379-15696DF9D31D}"), cm.registry_client_state_goopdate(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientStateMedium\\"), cm.machine_registry_client_state_medium());  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\"), cm.user_registry_update());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\"), cm.machine_registry_update());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\"), cm.registry_update(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\"), cm.registry_update(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\"), cm.user_registry_google());
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\"), cm.machine_registry_google());
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\"), cm.registry_google(false));
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\"), cm.registry_google(true));
}

TEST(OmahaCustomizationTest, IsInternalUser) {
  if (IsBuildSystem()) {
  // The build system is not configured the same.
  // This may or may not be true in non-Google Update builds.
#ifdef GOOGLE_UPDATE_BUILD
    EXPECT_FALSE(ConfigManager::Instance()->IsInternalUser());
#else
  std::wcout << _T("Did not test IsInternalUser.") << std::endl;
#endif
  } else {
    EXPECT_TRUE(ConfigManager::Instance()->IsInternalUser());
  }
}

//
// Test helpers.
//

TEST(OmahaCustomizationTest, GetGoogleUserPath) {
  EXPECT_STREQ(GetLocalAppDataPath() + SHORT_COMPANY_NAME + _T("\\"),
               GetGoogleUserPath());
}

TEST(OmahaCustomizationTest, GetGoogleUpdateUserPath) {
  EXPECT_STREQ(GetLocalAppDataPath() + SHORT_COMPANY_NAME + _T("\\")
                                     + PRODUCT_NAME + _T("\\"),
               GetGoogleUpdateUserPath());
}

// Assumes Program Files is in the normal location.
TEST(OmahaCustomizationTest, GetGoogleUpdateMachinePath) {
  CString expected_machine_path;
  EXPECT_SUCCEEDED(GetFolderPath(CSIDL_PROGRAM_FILES | CSIDL_FLAG_DONT_VERIFY,
                                 &expected_machine_path));
  expected_machine_path.Append(_T("\\") SHORT_COMPANY_NAME
                               _T("\\") PRODUCT_NAME);
  EXPECT_STREQ(expected_machine_path, GetGoogleUpdateMachinePath());
}

}  // namespace omaha
