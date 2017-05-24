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

#pragma once

#include <KWindowSystem>
#include <QPushButton>

namespace Budgie
{
    /**
     * Panel is a top level window on screen used as a panel like object
     */
    class TaskButton : public QPushButton
    {
        Q_OBJECT

    public:
        explicit TaskButton(KWindowInfo &window);
        void updateFromWindow(KWindowInfo &window, unsigned int changedProperties = 0);
    };
}
