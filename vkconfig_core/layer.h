/*
 * Copyright (c) 2020 Valve Corporation
 * Copyright (c) 2020 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * The vkConfig2 program monitors and adjusts the Vulkan configuration
 * environment. These settings are wrapped in this class, which serves
 * as the "model" of the system.
 *
 * Authors:
 * - Richard S. Wright Jr. <richard@lunarg.com>
 * - Christophe Riccio <christophe@lunarg.com>
 */

#pragma once

#include "../vkconfig_core/layer_setting.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include <vector>

void RemoveString(QString& delimitedString, QString value);
void AddString(QString& delimitedString, QString value);

// The value of this enum can't be changed
enum LayerState {
    LAYER_STATE_APPLICATION_CONTROLLED = 0,  // The Vulkan application configured this layer at will
    LAYER_STATE_OVERRIDDEN = 1,              // Force on/override this layer and configure it regarless of the Vulkan application
    LAYER_STATE_EXCLUDED = 2,                // Force off/exclude this layer regarless of the Vulkan application

    LAYER_STATE_FIRST = LAYER_STATE_APPLICATION_CONTROLLED,
    LAYER_STATE_LAST = LAYER_STATE_EXCLUDED
};

enum { LAYER_STATE_COUNT = LAYER_STATE_LAST - LAYER_STATE_FIRST + 1 };

class Layer {
   public:
    Layer();
    ~Layer();

    bool IsValid() const;
    bool operator==(const Layer& layer) const;
    bool operator!=(const Layer& layer) const;

   public:
    // Standard pieces of a layer
    QString _file_format_version;
    QString _name;
    QString _type;
    QString _library_path;  // This is a relative path, straight out of the json
    QString _api_version;
    QString _implementation_version;
    QString _description;

    QString _layer_path;  // Actual path to the folder that contains the layer (this is important!)
    LayerType _layer_type;

    // This layers settings. This will be used to build the editor
    // as well as create settings files. This CAN be empty if the
    // layer doens't have any settings.
    std::vector<LayerSetting> _layer_settings;

    LayerState _state;
    int _rank;  // When used in a configurate, what is the rank? (0 being first layer)

    // File based layers
    bool Load(QString full_path_to_file, LayerType layer_type);
};

void SortByRank(QVector<Layer*>& layers);