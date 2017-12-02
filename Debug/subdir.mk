################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Board.cpp \
../ComputerPlayer.cpp \
../Coordinator.cpp \
../HumanPlayer.cpp \
../Validator.cpp \
../main.cpp 

O_SRCS += \
../Board.o \
../ComputerPlayer.o \
../Coordinator.o \
../HumanPlayer.o \
../Validator.o \
../main.o 

OBJS += \
./Board.o \
./ComputerPlayer.o \
./Coordinator.o \
./HumanPlayer.o \
./Validator.o \
./main.o 

CPP_DEPS += \
./Board.d \
./ComputerPlayer.d \
./Coordinator.d \
./HumanPlayer.d \
./Validator.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


