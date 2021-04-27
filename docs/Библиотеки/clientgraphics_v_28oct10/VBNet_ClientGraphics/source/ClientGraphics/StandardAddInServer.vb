Imports Inventor
Imports System.Runtime.InteropServices
Imports Microsoft.Win32

Namespace ClientGraphics
    <ProgIdAttribute("ClientGraphics.StandardAddInServer"), _
    GuidAttribute("5f2b51ca-9aa8-4e7b-9d95-c4d9c1834cac")> _
    Public Class StandardAddInServer
        Implements Inventor.ApplicationAddInServer

        ' Inventor application object.
        Private m_inventorApplication As Inventor.Application


        ' GUID of the AddIn
        Private m_ClientId As String

        ' Variables for Screenshot
        'button defintion of Client Graphics
        Private WithEvents oCGButtonDef As ButtonDefinition
     


#Region "ApplicationAddInServer Members"

        Public Sub Activate(ByVal addInSiteObject As Inventor.ApplicationAddInSite, ByVal firstTime As Boolean) Implements Inventor.ApplicationAddInServer.Activate

            ' This method is called by Inventor when it loads the AddIn.
            ' The AddInSiteObject provides access to the Inventor Application object.
            ' The FirstTime flag indicates if the AddIn is loaded for the first time.

            ' Initialize AddIn members.
            m_inventorApplication = addInSiteObject.Application

            ' TODO:  Add ApplicationAddInServer.Activate implementation.
            ' e.g. event initialization, command creation etc.

            m_ClientId = "{5f2b51ca-9aa8-4e7b-9d95-c4d9c1834cac}"

            'icons for buttons
            Dim largeIconSize As Integer = 32

            Dim smallPicture1 As stdole.IPictureDisp = _
        Microsoft.VisualBasic.Compatibility.VB6.IconToIPicture( _
          New System.Drawing.Icon(My.Resources.CGIcon, 16, 16))
            Dim largePicture1 As stdole.IPictureDisp = _
              Microsoft.VisualBasic.Compatibility.VB6.IconToIPicture( _
                New System.Drawing.Icon( _
                  My.Resources.CGIcon, _
                  largeIconSize, _
                  largeIconSize))


            Dim controlDefs As ControlDefinitions = m_inventorApplication.CommandManager.ControlDefinitions

            'Screenshot button
            oCGButtonDef = _
              controlDefs.AddButtonDefinition( _
                "Client Graphics", "ClientGraphics:CGDef", _
                CommandTypesEnum.kNonShapeEditCmdType, m_ClientId, , "Client Graphics", _
                smallPicture1, largePicture1)

            If m_inventorApplication.UserInterfaceManager.InterfaceStyle = InterfaceStyleEnum.kRibbonInterface Then  'add Ribbon UI
                AddRibbonUI()
            Else  'Add Classic UI

                AddClassicUI()
            End If



        End Sub

        Public Sub Deactivate() Implements Inventor.ApplicationAddInServer.Deactivate

            ' This method is called by Inventor when the AddIn is unloaded.
            ' The AddIn will be unloaded either manually by the user or
            ' when the Inventor session is terminated.

            ' TODO:  Add ApplicationAddInServer.Deactivate implementation

            ' Release objects.
            Marshal.ReleaseComObject(m_inventorApplication)
            m_inventorApplication = Nothing

            System.GC.WaitForPendingFinalizers()
            System.GC.Collect()

        End Sub

        Public ReadOnly Property Automation() As Object Implements Inventor.ApplicationAddInServer.Automation

            ' This property is provided to allow the AddIn to expose an API 
            ' of its own to other programs. Typically, this  would be done by
            ' implementing the AddIn's API interface in a class and returning 
            ' that class object through this property.

            Get
                Return Nothing
            End Get

        End Property

        Public Sub ExecuteCommand(ByVal commandID As Integer) Implements Inventor.ApplicationAddInServer.ExecuteCommand

            ' Note:this method is now obsolete, you should use the 
            ' ControlDefinition functionality for implementing commands.

        End Sub

        Private Sub AddRibbonUI()
            Dim ribNames() As String = _
              {"Drawing", "Part", "Assembly", "Presentation"}

            For Each ribName In ribNames
                Dim oRibbon As Object = _
                  m_inventorApplication.UserInterfaceManager.Ribbons(ribName)
                Dim oTab As Object = oRibbon.RibbonTabs("id_TabTools")
                Dim oCGPanel As Object

                Try
                    oCGPanel = _
                      oTab.RibbonPanels("ClientGraphics:RibbonPanel")
                Catch ex As Exception
                    oCGPanel = _
                      oTab.RibbonPanels.Add( _
                        "ClientGraphics", "ClientGraphics:RibbonPanel", m_ClientId)
                End Try
                oCGPanel.CommandControls.AddButton(oCGButtonDef, True)
            Next
        End Sub

        Private Sub AddClassicUI()

            Dim classicUIToolsMenuNames() As String = _
              {"PartToolsMenu", "AssemblyToolsMenu", "DrawingMangerToolsMenu", _
               "PresentationToolsMenu"}

            For Each classicUIToolsMenuName In classicUIToolsMenuNames

                Try
                    Dim oToolsMenu As Object = _
                    m_inventorApplication.UserInterfaceManager.CommandBars( _
                      classicUIToolsMenuName)

                    If Not oToolsMenu Is Nothing Then
                        'delete if exists
                        Dim oCommandBarCtrl As Object
                        For Each oCommandBarCtrl In oToolsMenu.Controls
                            Dim oCtrolDef As Object
                            oCtrolDef = oCommandBarCtrl.ControlDefinition
                            If Not oCtrolDef Is Nothing Then
                                If oCtrolDef.InternalName = "ClientGraphics:CGDef" Then
                                    oCommandBarCtrl.Delete()
                                End If
                            End If
                        Next

                        'add the button
                        oToolsMenu.Controls.AddButton(oCGButtonDef)
                    End If

                Catch ex As Exception
                End Try
            Next
        End Sub

#End Region

#Region "COM Registration"

        ' Registers this class as an AddIn for Inventor.
        ' This function is called when the assembly is registered for COM.
        <ComRegisterFunctionAttribute()> _
        Public Shared Sub Register(ByVal t As Type)

            Dim clssRoot As RegistryKey = Registry.ClassesRoot
            Dim clsid As RegistryKey = Nothing
            Dim subKey As RegistryKey = Nothing

            Try
                clsid = clssRoot.CreateSubKey("CLSID\" + AddInGuid(t))
                clsid.SetValue(Nothing, "ClientGraphics")
                subKey = clsid.CreateSubKey("Implemented Categories\{39AD2B5C-7A29-11D6-8E0A-0010B541CAA8}")
                subKey.Close()

                subKey = clsid.CreateSubKey("Settings")
                subKey.SetValue("AddInType", "Standard")
                subKey.SetValue("LoadOnStartUp", "1")

                'subKey.SetValue("SupportedSoftwareVersionLessThan", "")
                subKey.SetValue("SupportedSoftwareVersionGreaterThan", "14..")
                'subKey.SetValue("SupportedSoftwareVersionEqualTo", "")
                'subKey.SetValue("SupportedSoftwareVersionNotEqualTo", "")
                'subKey.SetValue("Hidden", "0")
                'subKey.SetValue("UserUnloadable", "1")
                subKey.SetValue("Version", 0)
                subKey.Close()

                subKey = clsid.CreateSubKey("Description")
                subKey.SetValue(Nothing, "ClientGraphics")

            Catch ex As Exception
                System.Diagnostics.Trace.Assert(False)
            Finally
                If Not subKey Is Nothing Then subKey.Close()
                If Not clsid Is Nothing Then clsid.Close()
                If Not clssRoot Is Nothing Then clssRoot.Close()
            End Try

        End Sub

        ' Unregisters this class as an AddIn for Inventor.
        ' This function is called when the assembly is unregistered.
        <ComUnregisterFunctionAttribute()> _
        Public Shared Sub Unregister(ByVal t As Type)

            Dim clssRoot As RegistryKey = Registry.ClassesRoot
            Dim clsid As RegistryKey = Nothing

            Try
                clssRoot = Microsoft.Win32.Registry.ClassesRoot
                clsid = clssRoot.OpenSubKey("CLSID\" + AddInGuid(t), True)
                clsid.SetValue(Nothing, "")
                clsid.DeleteSubKeyTree("Implemented Categories\{39AD2B5C-7A29-11D6-8E0A-0010B541CAA8}")
                clsid.DeleteSubKeyTree("Settings")
                clsid.DeleteSubKeyTree("Description")
            Catch
            Finally
                If Not clsid Is Nothing Then clsid.Close()
                If Not clssRoot Is Nothing Then clssRoot.Close()
            End Try

        End Sub

        ' This property uses reflection to get the value for the GuidAttribute attached to the class.
        Public Shared ReadOnly Property AddInGuid(ByVal t As Type) As String
            Get
                Dim guid As String = ""
                Try
                    Dim customAttributes() As Object = t.GetCustomAttributes(GetType(GuidAttribute), False)
                    Dim guidAttribute As GuidAttribute = CType(customAttributes(0), GuidAttribute)
                    guid = "{" + guidAttribute.Value.ToString() + "}"
                Finally
                    AddInGuid = guid
                End Try
            End Get
        End Property

#End Region

        Private Sub oCGButtonDef_OnExecute(ByVal Context As Inventor.NameValueMap) Handles oCGButtonDef.OnExecute

            'dialog of Client Graphics 
            Dim oCGFDlg As CGDialog = New CGDialog()
            oCGFDlg.invApp = m_inventorApplication
            
            oCGFDlg.ShowDialog()
        End Sub
    End Class

End Namespace

