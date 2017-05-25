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

#include "panel_private.h"
#include <QDebug>

namespace Budgie
{
    /**
     * Handle the main widget construction
     */
    Panel::Panel() : d_ptr(new PanelPrivate(this))
    {
        Q_D(Panel);

        qDebug() << "I am a panel";

        auto layout = new QHBoxLayout;
        this->setLayout(layout);
        layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        // Force main panel size
        // setFixedSize(400, 50);
        layout->setMargin(0);

        d->setupChild();
        d->hookupSignals();
    }

    /**
     * Just reference back to our panel
     */
    PanelPrivate::PanelPrivate(Panel *p) : q_ptr(p)
    {
    }

    /**
     * hook up signals to KWindowSystem
     */
    void PanelPrivate::hookupSignals()
    {
        connect(KWindowSystem::self(),
                &KWindowSystem::windowAdded,
                this,
                &PanelPrivate::windowAdded);
        connect(KWindowSystem::self(),
                &KWindowSystem::windowRemoved,
                this,
                &PanelPrivate::windowRemoved);

        // The ugliness of overloaded signals reveal themselves.
        connect(KWindowSystem::self(),
                static_cast<void (KWindowSystem::*)(WId, NET::Properties, NET::Properties2)>(
                    &KWindowSystem::windowChanged),
                this,
                &PanelPrivate::windowChanged);
    }

    void PanelPrivate::setupChild()
    {
        Q_Q(Panel);
        auto child = new QWidget;
        child->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        q->layout()->addWidget(child);
        child->show();
        this->buttonLayout = new QHBoxLayout;
        this->buttonLayout->setMargin(0);
        this->buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        child->setLayout(this->buttonLayout);
    }

    /**
     * A window got added to the screen. Go poke it.
     */
    void PanelPrivate::windowAdded(WId id)
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
        buttons.insert(id, button);
        this->buttonLayout->addWidget(button);
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        button->show();
    }

    void PanelPrivate::windowRemoved(WId id)
    {
        auto button = buttons.take(id);
        if (!button) {
            qDebug() << "Removed unknown window " << id;
            return;
        }
        delete button;
    }

    void PanelPrivate::windowChanged(WId id, NET::Properties changedProperties,
                                     NET::Properties2 ignored)
    {
        auto button = buttons.value(id, nullptr);
        if (!button) {
            qDebug() << "Unknown window changed: " << id;
            return;
        }

        if (changedProperties == 0) {
            return;
        }

        KWindowInfo info(id, changedProperties, ignored);
        if (!info.valid()) {
            qDebug() << "Invalid window: " << id;
            return;
        }

        button->updateFromWindow(info, changedProperties);
    }
}
