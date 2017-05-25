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

#include <QWidget>

namespace Budgie
{
    QT_FORWARD_DECLARE_CLASS(PanelPrivate)

    class Panel : public QWidget
    {
        Q_OBJECT

    public:
        explicit Panel();

    protected:
        Q_DECLARE_PRIVATE(Panel);

    private:
        const QSharedPointer<PanelPrivate> d_ptr;
    };
}
