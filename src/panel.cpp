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
#include <QDebug>

namespace Budgie
{
    /**
     * Main constructor for a Budgie::Panel
     */
    Panel::Panel()
    {
        qDebug() << "I am a panel";
        this->windows.reset(new QMap<WId, KWindowInfo *>);
        connect(KWindowSystem::self(), &KWindowSystem::windowAdded, this, &Panel::windowAdded);
        connect(KWindowSystem::self(), &KWindowSystem::windowRemoved, this, &Panel::windowRemoved);
    }

    /**
     * A window got added to the screen. Go poke it.
     */
    void Panel::windowAdded(WId id)
    {
        static auto basicQueryMask = NET::WMName | NET::WMWindowType;
        QScopedPointer<KWindowInfo> info(new KWindowInfo(id, basicQueryMask));

        if (!info->valid()) {
            qDebug() << "Invalid window: " << id;
            return;
        }

        if (windows->contains(id)) {
            return;
        }

        qDebug() << "New window: " << info->name();
        windows->insert(id, info.take());
    }

    void Panel::windowRemoved(WId id)
    {
        KWindowInfo *info = this->windows->take(id);
        if (!info) {
            qDebug() << "Removed unknown window " << id;
            return;
        }
        qDebug() << "Removed window " << info->name();
        delete info;
    }
}
