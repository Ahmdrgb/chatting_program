/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : chat application                                        */
/* !Description     : chat application                                        */
/*                                                                            */
/* !File            : chat_interface.h                                        */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : chat program | EME - CLASS 1                            */
/*                                                                            */
/* !Target          : TIVA-C TM4C123GH6PM                                     */
/*                                                                            */
/* !Compiler        : Code Composer Studio 8.3.1                              */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed Ragab,ahmed abdellazem     !Date : sep 10, 2023   */
/* !Coded by        : Ahmed Ragab,ahmed abdellazem    !Date : sep 10, 2023    */
/*                                                                            */
/* Ver 1.0    sep 15, 2023     Initial release                                */
/******************************************************************************/

#ifndef APP_INC_CHAT_INTERFACE_H_
#define APP_INC_CHAT_INTERFACE_H_

void Chat_Run(void);
void State_Idle(void);
void State_Listner(void);
void State_Chatting(void);
void Switch_Handler(void);

#endif /* APP_INC_CHAT_INTERFACE_H_ */
