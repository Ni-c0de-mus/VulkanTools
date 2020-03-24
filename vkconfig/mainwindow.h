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
 * Author: Richard S. Wright Jr. <richard@lunarg.com>
 */

#pragma once
#include <QVector>

#include <QMainWindow>
#include <QListWidgetItem>

#include <vulkanconfiguration.h>
#include <settingseditor.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    CVulkanConfiguration*    pVulkanConfig;
    CSettingsEditor*         pSettingsEditor;

public Q_SLOTS:
    void fileExit(bool bChecked);
    void fileHistory(bool bChecked);

    void aboutVkConfig(bool bChecked);
    void toolsVulkanInfo(bool bChecked);
    void toolsVulkanInstallation(bool bChecked);
    void toolsVulkanTestApp(bool bChecked);
    void toolsSetCustomPaths(bool bChecked);

    void profileItemChanged(QListWidgetItem *item);
    void currentProfileRowChanged(int row);

    void on_pushButtonCustomPaths_clicked();    // Fired by menu even if no button
    void on_pushButtonLaunch_clicked();         // Ditto

    void on_pushButtonAppList_clicked(void);
    void on_pushButtonEditProfile_clicked(void);



private:
    Ui::MainWindow *ui;
};

