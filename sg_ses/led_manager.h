// led_manager.h

#ifndef _LED_MANAGER_H_
#define _LED_MANAGER_H_

/*
 * Define LED status, use for function led_set_status
 */
#define LED_REBUILD     "1:1:1"
#define LED_RAID_FAILED "1:2:1"
#define LED_HOT_SPARE   "1:5:1"

#define LED_IDENT       "2:1:1"
#define LED_REMOVE      "2:2:1"
#define LED_INSERT      "2:3:1"
#define LED_MISSING     "2:4:1"

#define LED_FAULT       "3:5:1"

/*
 * Do initialization
 */
void led_init();

/*
 * Function  : manage expander LED light status
 * Parameters:
 *      chassis_index 
 *             index of chassis, 0 for main chassis, 1..n for extern chassis
 *      slot_index
 *             slot index
 *      type
 *             define by macro LED_XXX, see the head of this file.
 *      status
 *             0 for clearing status, other for setting.
 * Return    : void
 */
void led_set_status(int chassis_index, int slot_index, char *type, int status);

#endif // _LED_MANAGER_H_

