#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);
/*
	frontLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	backLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	frontRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	middleRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	backRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	scorer.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {

	while(1) {
		frontLeftMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)));
		frontRightMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)));
		middleLeftMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)));
		middleRightMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)));
		backLeftMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)));
		backRightMotor.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)));

		bool L1TON = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
		bool L2TON = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
		intake.move((127.0 * (L1TON - L2TON)));

		bool R1TON = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
		if(R1TON)
			scorer.move(127);
		else
			scorer.move(0);

		pros::delay(10);
	}
}