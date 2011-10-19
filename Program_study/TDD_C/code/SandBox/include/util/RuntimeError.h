/*
 * RuntimeError.h
 *
 *  Created on: 2011/09/18
 *      Author: TSUNEMICHI
 */

#ifndef RUNTIMEERROR_H_
#define RUNTIMEERROR_H_

void RuntimeError(const char* message, int parameter,
                  const char* file, int line);

#define RUNTIME_ERROR(description, parameter)\
  RuntimeError(description, parameter, __FILE__, __LINE__)

#endif /* RUNTIMEERROR_H_ */
