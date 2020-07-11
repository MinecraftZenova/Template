#workaround for the directory symlinks

import os
import argparse
import win32security
import ntsecuritycon as con

parser = argparse.ArgumentParser(description='Add \'ALL APPLICATION PACKAGES\' security')
parser.add_argument('directory', metavar='file', type=str, nargs='?', help='directory or file')
args = parser.parse_args()

directory = args.directory

path = os.path.abspath(directory)
app_package, domain, type = win32security.LookupAccountName ("", "all application packages")

sd = win32security.GetNamedSecurityInfo(path, win32security.SE_FILE_OBJECT, win32security.DACL_SECURITY_INFORMATION)
dacl = sd.GetSecurityDescriptorDacl()   # instead of dacl = win32security.ACL()

dacl.AddAccessAllowedAceEx(win32security.ACL_REVISION_DS, win32security.OBJECT_INHERIT_ACE | win32security.CONTAINER_INHERIT_ACE, con.FILE_ALL_ACCESS, app_package)

sd.SetSecurityDescriptorDacl(1, dacl, 0)   # may not be necessary
win32security.SetFileSecurity(path, win32security.DACL_SECURITY_INFORMATION, sd)