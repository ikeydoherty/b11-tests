/*
 * This file is part of b11-tests
 *
 * Copyright © 2017 Ikey Doherty <ikey@solus-project.com>
 *
 * b11-tests is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include "taskbutton.h"

namespace Budgie
{
    TaskButton::TaskButton(KWindowInfo &window)
    {
        this->updateFromWindow(window);
    }

    void TaskButton::updateFromWindow(KWindowInfo &window, unsigned int changedProperties)
    {
        bool setIcon = false;
        bool setName = false;

        if (changedProperties == 0) {
            setIcon = true;
            setName = true;
        }

        if (changedProperties & NET::WMIcon || changedProperties & NET::WMIconName) {
            setIcon = true;
        }
        if (changedProperties & NET::WMName || changedProperties & NET::WMVisibleName) {
            setName = true;
        }

        if (setName) {
            this->setText(window.name());
        }
        if (setIcon) {
            auto icon = KWindowSystem::icon(window.win());
            this->setIcon(QIcon(icon));
        }
    }
}
