################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Board.cpp \
../src/ComputerPlayer.cpp \
../src/Validator.cpp 

OBJS += \
./src/Board.o \
./src/ComputerPlayer.o \
./src/Validator.o 

CPP_DEPS += \
./src/Board.d \
./src/ComputerPlayer.d \
./src/Validator.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/gal/workspace/UnitTestsReversi/include" -I"/home/gal/workspace/UnitTestsReversi/gtest_src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


