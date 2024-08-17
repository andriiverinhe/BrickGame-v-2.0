/**
 * @file QBaseController.hpp
 * @author nenamaxi (an.veringe@gmail.com)
 * @brief Header file base controller
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <QKeyEvent>
#include <QObject>
#include <QTimer>

namespace s21 {

/**
 * @brief A base class for game controllers.
 */
class QBaseGameController : public QObject {
  Q_OBJECT

 protected:
  QTimer *timer_input;  /**< Timer user input update */
  QTimer *timer_output; /**< Timer interface update */

 public:
  /**
   * @brief The default constructor for QBaseGameController.
   *
   * @param parent The parent object.
   */
  explicit QBaseGameController(QObject *parent = nullptr)
      : QObject(parent),
        timer_input(new QTimer(this)),
        timer_output(new QTimer(this)){};

  /**
   * @brief The destructor for QBaseGameController.
   */
  virtual ~QBaseGameController() = default;

  /**
   * @brief Runs the game controller.
   */
  virtual void run() = 0;

  /**
   * @brief Stops the game controller.
   */
  virtual void stop() = 0;

 public slots:
  /**
   * @brief Updates the game view.
   *
   */
  virtual void updateView() = 0;

  /**
   * @brief Sends an input signal.
   *
   */
  virtual void sendInputSignal() = 0;

  /**
   * @brief Handles a user action received event.
   *
   * @param event The user action received event.
   */
  virtual void onUserActionReceived(const QKeyEvent *event) = 0;

 signals:
  /**
   * @brief Signals that the game controller has finished.
   */
  void finished();
};

}  // namespace s21
