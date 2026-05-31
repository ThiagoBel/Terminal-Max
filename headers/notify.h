#ifndef NOTIFY_H
#define NOTIFY_H

#include <windows.h>

namespace notify
{
    enum class NotifyIcon
    {
        Information,
        Warning,
        Error,
        Question,
        None
    };

    enum class NotifyButtons
    {
        Ok,
        OkCancel,
        YesNo,
        YesNoCancel,
        RetryCancel
    };

    int notify(
        const char *message,
        const char *title = "Aviso",
        NotifyIcon icon = NotifyIcon::Information,
        NotifyButtons buttons = NotifyButtons::Ok)
    {
        UINT uType = 0;

        switch (icon)
        {
        case NotifyIcon::Information:
            uType |= MB_ICONINFORMATION;
            break;
        case NotifyIcon::Warning:
            uType |= MB_ICONWARNING;
            break;
        case NotifyIcon::Error:
            uType |= MB_ICONERROR;
            break;
        case NotifyIcon::Question:
            uType |= MB_ICONQUESTION;
            break;
        case NotifyIcon::None:
            uType |= 0;
            break;
        }

        switch (buttons)
        {
        case NotifyButtons::Ok:
            uType |= MB_OK;
            break;
        case NotifyButtons::OkCancel:
            uType |= MB_OKCANCEL;
            break;
        case NotifyButtons::YesNo:
            uType |= MB_YESNO;
            break;
        case NotifyButtons::YesNoCancel:
            uType |= MB_YESNOCANCEL;
            break;
        case NotifyButtons::RetryCancel:
            uType |= MB_RETRYCANCEL;
            break;
        }

        return MessageBoxA(NULL, message ? message : "", title ? title : "Aviso", uType);
    }
}
#endif