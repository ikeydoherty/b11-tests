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

        auto layout = new QHBoxLayout;
        this->setLayout(layout);
        layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        // Force main panel size
        // setFixedSize(400, 50);
        layout->setMargin(0);

        setupChild();

        // Hook up signals
        connect(KWindowSystem::self(), &KWindowSystem::windowAdded, this, &Panel::windowAdded);
        connect(KWindowSystem::self(), &KWindowSystem::windowRemoved, this, &Panel::windowRemoved);
    }

    void Panel::setupChild()
    {
        auto child = new QWidget;
        child->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        this->layout()->addWidget(child);
        child->show();
        this->buttonLayout = new QHBoxLayout;
        this->buttonLayout->setMargin(0);
        this->buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        child->setLayout(this->buttonLayout);
    }

    /**
     * A window got added to the screen. Go poke it.
     */
    void Panel::windowAdded(WId id)
    {
        if (buttons.contains(id)) {
            return;
        }
        static auto basicQueryMask =
            NET::WMName | NET::WMWindowType | NET::WMIcon | NET::WMIconName | NET::WMDesktop;
        static auto basicQueryMaskV2 = NET::WM2DesktopFileName;
        KWindowInfo info(id, basicQueryMask, basicQueryMaskV2);
        if (!info.valid()) {
            qDebug() << "Invalid window: " << id;
            return;
        }

        auto button = new TaskButton(info);
        qDebug() << "New window: " << info.name();
        buttons.insert(id, button);
        this->buttonLayout->addWidget(button);
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        button->show();
    }

    void Panel::windowRemoved(WId id)
    {
        auto button = buttons.take(id);
        if (!button) {
            qDebug() << "Removed unknown window " << id;
            return;
        }
        qDebug() << "Removed window " << button->text();
        delete button;
    }
}
