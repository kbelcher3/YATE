#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QSettings>
#include <QFileDialog>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>

#include "globals.h"

namespace Yate {
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog), settings_(new QSettings(this))
{
    ui->setupUi(this);

    reloadSettings();
    setAcceptDrops(true);
}

void SettingsDialog::setEEFilePath(QString &path)
{
    ui->lblLogFilePath->setText(path);
}

void SettingsDialog::reloadSettings()
{
    QVariant watershieldSetting = settings_->value(SETTINGS_KEY_WATERSHIELD);
    if(!watershieldSetting.isNull() && watershieldSetting.toString() == SETTINGS_OPT_SHARD) {
        ui->radWaterShieldShardIn->setChecked(true);
        ui->radWatershieldExact->setChecked(false);
    } else {
        ui->radWaterShieldShardIn->setChecked(false);
        ui->radWatershieldExact->setChecked(true);
    }
    if (!settings_->value(SETTINGS_KEY_EE_LOG).isNull()) {
        QString pth = settings_->value(SETTINGS_KEY_EE_LOG).toString();
        setEEFilePath(pth);
    }
}

void SettingsDialog::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void SettingsDialog::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        setEEFilePath(fileName);
        break;
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}


void SettingsDialog::on_btnSave_clicked()
{
  this->accept();
  if(!ui->lblLogFilePath->text().isEmpty()) {
      settings_->setValue(SETTINGS_KEY_EE_LOG, ui->lblLogFilePath->text().trimmed());
  }
  if (ui->radWaterShieldShardIn->isChecked()) {
      settings_->setValue(SETTINGS_KEY_WATERSHIELD, SETTINGS_OPT_SHARD);
  } else {
      settings_->setValue(SETTINGS_KEY_WATERSHIELD, SETTINGS_OPT_EXACT);
  }
}


void SettingsDialog::on_btnCancel_clicked()
{
  this->reject();
}


void SettingsDialog::on_btnBrowseLogPath_clicked()
{
    QString newPath = QFileDialog::getOpenFileName(this, tr("EE.log file"), QFileInfo( ui->lblLogFilePath->text()).dir().absolutePath(), tr("Log File (*.log)"));
    if(newPath.length()) {
        setEEFilePath(newPath);
    }
}


void SettingsDialog::on_btnResetFeedback_clicked()
{
  settings_->remove(SETTINGS_KEY_FEEDBACK_POS_X);
  settings_->remove(SETTINGS_KEY_FEEDBACK_POS_Y);
}

}
