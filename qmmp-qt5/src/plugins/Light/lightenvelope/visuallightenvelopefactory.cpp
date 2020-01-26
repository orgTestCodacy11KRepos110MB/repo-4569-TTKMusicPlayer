/* =================================================
 * This file is part of the TTK Music Player qmmp plugin project
 * Copyright (C) 2015 - 2020 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include <qmmp/qmmp.h>
#include "visuallightenvelopefactory.h"
#include "lightenvelope.h"

const LightProperties VisualLightEnvelopeFactory::properties() const
{
    LightProperties properties;
    properties.name = tr("Light Envelope Plugin");
    properties.shortName = "lightenvelope";
    properties.hasSettings = false;
    return properties;
}

Light *VisualLightEnvelopeFactory::create(QWidget *parent)
{
    return new LightEnvelope(parent);
}
