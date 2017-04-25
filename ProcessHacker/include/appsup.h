#ifndef PH_APPSUP_H
#define PH_APPSUP_H

extern GUID XP_CONTEXT_GUID;
extern GUID VISTA_CONTEXT_GUID;
extern GUID WIN7_CONTEXT_GUID;
extern GUID WIN8_CONTEXT_GUID;
extern GUID WINBLUE_CONTEXT_GUID;
extern GUID WINTHRESHOLD_CONTEXT_GUID;

typedef struct PACKAGE_ID PACKAGE_ID;

// begin_phapppub
PHAPPAPI
BOOLEAN
NTAPI
PhGetProcessIsSuspended(
    _In_ PSYSTEM_PROCESS_INFORMATION Process
    );
// end_phapppub

NTSTATUS PhGetProcessSwitchContext(
    _In_ HANDLE ProcessHandle,
    _Out_ PGUID Guid
    );

PPH_STRING PhGetProcessPackageFullName(
    _In_ HANDLE ProcessHandle
    );

PACKAGE_ID *PhPackageIdFromFullName(
    _In_ PWSTR PackageFullName
    );

PPH_STRING PhGetPackagePath(
    _In_ PACKAGE_ID *PackageId
    );

// begin_phapppub
typedef enum _PH_KNOWN_PROCESS_TYPE
{
    UnknownProcessType,
    SystemProcessType, // ntoskrnl/ntkrnlpa/...
    SessionManagerProcessType, // smss
    WindowsSubsystemProcessType, // csrss
    WindowsStartupProcessType, // wininit
    ServiceControlManagerProcessType, // services
    LocalSecurityAuthorityProcessType, // lsass
    LocalSessionManagerProcessType, // lsm
    WindowsLogonProcessType, // winlogon
    ServiceHostProcessType, // svchost
    RunDllAsAppProcessType, // rundll32
    ComSurrogateProcessType, // dllhost
    TaskHostProcessType, // taskeng, taskhost, taskhostex
    ExplorerProcessType, // explorer
    UmdfHostProcessType, // wudfhost
    MaximumProcessType,
    KnownProcessTypeMask = 0xffff,

    KnownProcessWow64 = 0x20000
} PH_KNOWN_PROCESS_TYPE;

PHAPPAPI
NTSTATUS
NTAPI
PhGetProcessKnownType(
    _In_ HANDLE ProcessHandle,
    _Out_ PH_KNOWN_PROCESS_TYPE *KnownProcessType
    );

typedef union _PH_KNOWN_PROCESS_COMMAND_LINE
{
    struct
    {
        PPH_STRING GroupName;
    } ServiceHost;
    struct
    {
        PPH_STRING FileName;
        PPH_STRING ProcedureName;
    } RunDllAsApp;
    struct
    {
        GUID Guid;
        PPH_STRING Name; // optional
        PPH_STRING FileName; // optional
    } ComSurrogate;
} PH_KNOWN_PROCESS_COMMAND_LINE, *PPH_KNOWN_PROCESS_COMMAND_LINE;

PHAPPAPI
BOOLEAN
NTAPI
PhaGetProcessKnownCommandLine(
    _In_ PPH_STRING CommandLine,
    _In_ PH_KNOWN_PROCESS_TYPE KnownProcessType,
    _Out_ PPH_KNOWN_PROCESS_COMMAND_LINE KnownCommandLine
    );
// end_phapppub

VOID PhEnumChildWindows(
    _In_opt_ HWND hWnd,
    _In_ ULONG Limit,
    _In_ WNDENUMPROC Callback,
    _In_ LPARAM lParam
    );

HWND PhGetProcessMainWindow(
    _In_ HANDLE ProcessId,
    _In_opt_ HANDLE ProcessHandle
    );

PPH_STRING PhGetServiceRelevantFileName(
    _In_ PPH_STRINGREF ServiceName,
    _In_ SC_HANDLE ServiceHandle
    );

PPH_STRING PhEscapeStringForDelimiter(
    _In_ PPH_STRING String,
    _In_ WCHAR Delimiter
    );

PPH_STRING PhUnescapeStringForDelimiter(
    _In_ PPH_STRING String,
    _In_ WCHAR Delimiter
    );

typedef struct mxml_node_s mxml_node_t;

PPH_STRING PhGetOpaqueXmlNodeText(
    _In_ mxml_node_t *node
    );

// begin_phapppub
PHAPPAPI
VOID
NTAPI
PhSearchOnlineString(
    _In_ HWND hWnd,
    _In_ PWSTR String
    );

PHAPPAPI
VOID
NTAPI
PhShellExecuteUserString(
    _In_ HWND hWnd,
    _In_ PWSTR Setting,
    _In_ PWSTR String,
    _In_ BOOLEAN UseShellExecute,
    _In_opt_ PWSTR ErrorMessage
    );

PHAPPAPI
VOID
NTAPI
PhLoadSymbolProviderOptions(
    _Inout_ PPH_SYMBOL_PROVIDER SymbolProvider
    );
// end_phapppub

PWSTR PhMakeContextAtom(
    VOID
    );

// begin_phapppub
PHAPPAPI
VOID
NTAPI
PhCopyListViewInfoTip(
    _Inout_ LPNMLVGETINFOTIP GetInfoTip,
    _In_ PPH_STRINGREF Tip
    );

PHAPPAPI
VOID
NTAPI
PhCopyListView(
    _In_ HWND ListViewHandle
    );

PHAPPAPI
VOID
NTAPI
PhHandleListViewNotifyForCopy(
    _In_ LPARAM lParam,
    _In_ HWND ListViewHandle
    );
// end_phapppub

#define PH_LIST_VIEW_CTRL_C_BEHAVIOR 0x1
#define PH_LIST_VIEW_CTRL_A_BEHAVIOR 0x2
#define PH_LIST_VIEW_DEFAULT_1_BEHAVIORS (PH_LIST_VIEW_CTRL_C_BEHAVIOR | PH_LIST_VIEW_CTRL_A_BEHAVIOR)

VOID PhHandleListViewNotifyBehaviors(
    _In_ LPARAM lParam,
    _In_ HWND ListViewHandle,
    _In_ ULONG Behaviors
    );

// begin_phapppub
PHAPPAPI
BOOLEAN
NTAPI
PhGetListViewContextMenuPoint(
    _In_ HWND ListViewHandle,
    _Out_ PPOINT Point
    );
// end_phapppub

HFONT PhDuplicateFontWithNewWeight(
    _In_ HFONT Font,
    _In_ LONG NewWeight
    );

VOID PhSetWindowOpacity(
    _In_ HWND WindowHandle,
    _In_ ULONG OpacityPercent
    );

#define PH_OPACITY_TO_ID(Opacity) (ID_OPACITY_10 + (10 - (Opacity) / 10) - 1)
#define PH_ID_TO_OPACITY(Id) (100 - (((Id) - ID_OPACITY_10) + 1) * 10)

// begin_phapppub
PHAPPAPI
VOID
NTAPI
PhLoadWindowPlacementFromSetting(
    _In_opt_ PWSTR PositionSettingName,
    _In_opt_ PWSTR SizeSettingName,
    _In_ HWND WindowHandle
    );

PHAPPAPI
VOID
NTAPI
PhSaveWindowPlacementToSetting(
    _In_opt_ PWSTR PositionSettingName,
    _In_opt_ PWSTR SizeSettingName,
    _In_ HWND WindowHandle
    );

PHAPPAPI
VOID
NTAPI
PhLoadListViewColumnsFromSetting(
    _In_ PWSTR Name,
    _In_ HWND ListViewHandle
    );

PHAPPAPI
VOID
NTAPI
PhSaveListViewColumnsToSetting(
    _In_ PWSTR Name,
    _In_ HWND ListViewHandle
    );

PHAPPAPI
PPH_STRING
NTAPI
PhGetPhVersion(
    VOID
    );

PHAPPAPI
VOID
NTAPI
PhGetPhVersionNumbers(
    _Out_opt_ PULONG MajorVersion,
    _Out_opt_ PULONG MinorVersion,
    _Reserved_ PULONG Reserved,
    _Out_opt_ PULONG RevisionNumber
    );

PHAPPAPI
VOID
NTAPI
PhWritePhTextHeader(
    _Inout_ PPH_FILE_STREAM FileStream
    );

#define PH_SHELL_APP_PROPAGATE_PARAMETERS 0x1
#define PH_SHELL_APP_PROPAGATE_PARAMETERS_IGNORE_VISIBILITY 0x2
#define PH_SHELL_APP_PROPAGATE_PARAMETERS_FORCE_SETTINGS 0x4

PHAPPAPI
BOOLEAN
NTAPI
PhShellProcessHacker(
    _In_opt_ HWND hWnd,
    _In_opt_ PWSTR Parameters,
    _In_ ULONG ShowWindowType,
    _In_ ULONG Flags,
    _In_ ULONG AppFlags,
    _In_opt_ ULONG Timeout,
    _Out_opt_ PHANDLE ProcessHandle
    );
// end_phapppub

BOOLEAN PhShellProcessHackerEx(
    _In_opt_ HWND hWnd,
    _In_opt_ PWSTR FileName,
    _In_opt_ PWSTR Parameters,
    _In_ ULONG ShowWindowType,
    _In_ ULONG Flags,
    _In_ ULONG AppFlags,
    _In_opt_ ULONG Timeout,
    _Out_opt_ PHANDLE ProcessHandle
    );

BOOLEAN PhCreateProcessIgnoreIfeoDebugger(
    _In_ PWSTR FileName
    );

// begin_phapppub
typedef struct _PH_TN_COLUMN_MENU_DATA
{
    HWND TreeNewHandle;
    PPH_TREENEW_HEADER_MOUSE_EVENT MouseEvent;
    ULONG DefaultSortColumn;
    PH_SORT_ORDER DefaultSortOrder;

    struct _PH_EMENU_ITEM *Menu;
    struct _PH_EMENU_ITEM *Selection;
    ULONG ProcessedId;
} PH_TN_COLUMN_MENU_DATA, *PPH_TN_COLUMN_MENU_DATA;

#define PH_TN_COLUMN_MENU_HIDE_COLUMN_ID ((ULONG)-1)
#define PH_TN_COLUMN_MENU_CHOOSE_COLUMNS_ID ((ULONG)-2)
#define PH_TN_COLUMN_MENU_SIZE_COLUMN_TO_FIT_ID ((ULONG)-3)
#define PH_TN_COLUMN_MENU_SIZE_ALL_COLUMNS_TO_FIT_ID ((ULONG)-4)
#define PH_TN_COLUMN_MENU_RESET_SORT_ID ((ULONG)-5)

PHAPPAPI
VOID
NTAPI
PhInitializeTreeNewColumnMenu(
    _Inout_ PPH_TN_COLUMN_MENU_DATA Data
    );
// end_phapppub

#define PH_TN_COLUMN_MENU_NO_VISIBILITY 0x1
#define PH_TN_COLUMN_MENU_SHOW_RESET_SORT 0x2

VOID PhInitializeTreeNewColumnMenuEx(
    _Inout_ PPH_TN_COLUMN_MENU_DATA Data,
    _In_ ULONG Flags
    );

// begin_phapppub
PHAPPAPI
BOOLEAN
NTAPI
PhHandleTreeNewColumnMenu(
    _Inout_ PPH_TN_COLUMN_MENU_DATA Data
    );

PHAPPAPI
VOID
NTAPI
PhDeleteTreeNewColumnMenu(
    _In_ PPH_TN_COLUMN_MENU_DATA Data
    );

typedef struct _PH_TN_FILTER_SUPPORT
{
    PPH_LIST FilterList;
    HWND TreeNewHandle;
    PPH_LIST NodeList;
} PH_TN_FILTER_SUPPORT, *PPH_TN_FILTER_SUPPORT;

typedef BOOLEAN (NTAPI *PPH_TN_FILTER_FUNCTION)(
    _In_ PPH_TREENEW_NODE Node,
    _In_opt_ PVOID Context
    );

typedef struct _PH_TN_FILTER_ENTRY
{
    PPH_TN_FILTER_FUNCTION Filter;
    PVOID Context;
} PH_TN_FILTER_ENTRY, *PPH_TN_FILTER_ENTRY;

PHAPPAPI
VOID
NTAPI
PhInitializeTreeNewFilterSupport(
    _Out_ PPH_TN_FILTER_SUPPORT Support,
    _In_ HWND TreeNewHandle,
    _In_ PPH_LIST NodeList
    );

PHAPPAPI
VOID
NTAPI
PhDeleteTreeNewFilterSupport(
    _In_ PPH_TN_FILTER_SUPPORT Support
    );

PHAPPAPI
PPH_TN_FILTER_ENTRY
NTAPI
PhAddTreeNewFilter(
    _In_ PPH_TN_FILTER_SUPPORT Support,
    _In_ PPH_TN_FILTER_FUNCTION Filter,
    _In_opt_ PVOID Context
    );

PHAPPAPI
VOID
NTAPI
PhRemoveTreeNewFilter(
    _In_ PPH_TN_FILTER_SUPPORT Support,
    _In_ PPH_TN_FILTER_ENTRY Entry
    );

PHAPPAPI
BOOLEAN
NTAPI
PhApplyTreeNewFiltersToNode(
    _In_ PPH_TN_FILTER_SUPPORT Support,
    _In_ PPH_TREENEW_NODE Node
    );

PHAPPAPI
VOID
NTAPI
PhApplyTreeNewFilters(
    _In_ PPH_TN_FILTER_SUPPORT Support
    );
// end_phapppub

typedef struct _PH_COPY_CELL_CONTEXT
{
    HWND TreeNewHandle;
    ULONG Id; // column ID
    PPH_STRING MenuItemText;
} PH_COPY_CELL_CONTEXT, *PPH_COPY_CELL_CONTEXT;

BOOLEAN PhInsertCopyCellEMenuItem(
    _In_ struct _PH_EMENU_ITEM *Menu,
    _In_ ULONG InsertAfterId,
    _In_ HWND TreeNewHandle,
    _In_ PPH_TREENEW_COLUMN Column
    );

BOOLEAN PhHandleCopyCellEMenuItem(
    _In_ struct _PH_EMENU_ITEM *SelectedItem
    );

BOOLEAN PhShellOpenKey2(
    _In_ HWND hWnd,
    _In_ PPH_STRING KeyName
    );

PPH_STRING PhPcre2GetErrorMessage(
    _In_ INT ErrorCode
    );

#define PH_LOAD_SHARED_ICON_SMALL(Name) PhLoadIcon(PhInstanceHandle, (Name), PH_LOAD_ICON_SHARED | PH_LOAD_ICON_SIZE_SMALL, 0, 0)
#define PH_LOAD_SHARED_ICON_LARGE(Name) PhLoadIcon(PhInstanceHandle, (Name), PH_LOAD_ICON_SHARED | PH_LOAD_ICON_SIZE_LARGE, 0, 0)

FORCEINLINE PVOID PhpGenericPropertyPageHeader(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam,
    _In_ PWSTR ContextName
    )
{
    PVOID context;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            LPPROPSHEETPAGE propSheetPage = (LPPROPSHEETPAGE)lParam;

            context = (PVOID)propSheetPage->lParam;
            SetProp(hwndDlg, ContextName, (HANDLE)context);
        }
        break;
    case WM_DESTROY:
        {
            context = (PVOID)GetProp(hwndDlg, ContextName);
            RemoveProp(hwndDlg, ContextName);
        }
        break;
    default:
        {
            context = (PVOID)GetProp(hwndDlg, ContextName);
        }
        break;
    }

    return context;
}

#define SWP_NO_ACTIVATE_MOVE_SIZE_ZORDER (SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER)
#define SWP_SHOWWINDOW_ONLY (SWP_NO_ACTIVATE_MOVE_SIZE_ZORDER | SWP_SHOWWINDOW)
#define SWP_HIDEWINDOW_ONLY (SWP_NO_ACTIVATE_MOVE_SIZE_ZORDER | SWP_HIDEWINDOW)

// splitter

typedef struct _PH_HSPLITTER_CONTEXT
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG Hot : 1;
            ULONG Pushed : 1;
            ULONG Moved : 1;
            ULONG DragMode : 1;
            ULONG Spare : 28;
        };
    };

    ULONG Height;
    PH_LAYOUT_MANAGER LayoutManager;
    PPH_LAYOUT_ITEM Topitem;
    PPH_LAYOUT_ITEM Bottomitem;
} PH_HSPLITTER_CONTEXT, *PPH_HSPLITTER_CONTEXT;

PPH_HSPLITTER_CONTEXT PhInitializeHSplitterSupport(
    _In_ HWND Parent,
    _In_ HWND TopChild,
    _In_ HWND BottomChild
    );

VOID PhDeleteHSplitterSupportSupport(
    _Inout_ PPH_HSPLITTER_CONTEXT Context
    );

VOID PhHSplitterHandleWmSize(
    _Inout_ PPH_HSPLITTER_CONTEXT Context,
    _In_ INT Width,
    _In_ INT Height
    );

VOID PhHSplitterHandleLButtonDown(
    _Inout_ PPH_HSPLITTER_CONTEXT Context,
    _In_ HWND hwnd,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    );

VOID PhHSplitterHandleLButtonUp(
    _Inout_ PPH_HSPLITTER_CONTEXT Context,
    _In_ HWND hwnd,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    );

VOID PhHSplitterHandleMouseMove(
    _Inout_ PPH_HSPLITTER_CONTEXT Context,
    _In_ HWND hwnd,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    );

VOID PhHSplitterHandleMouseLeave(
    _Inout_ PPH_HSPLITTER_CONTEXT Context,
    _In_ HWND hwnd,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    );

#endif
