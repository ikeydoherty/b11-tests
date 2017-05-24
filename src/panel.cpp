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

#include "panel.h"
#include <KWindowSystem>
#include <QDebug>

namespace Budgie
{
    /**
     * Main constructor for a Budgie::Panel
     */
    Panel::Panel()
    {
        qDebug() << "I am a panel";
        connect(KWindowSystem::self(), &KWindowSystem::windowAdded, this, &Panel::windowAdded);
        connect(KWindowSystem::self(), &KWindowSystem::windowRemoved, this, &Panel::windowRemoved);
    }

    void Panel::windowAdded(WId id)
    {
        qDebug() << "New window: " << id;
    }

    void Panel::windowRemoved(WId id)
    {
        qDebug() << "Removed window: " << id;
    }
}
