/**
 * \author Artur Pereira - 2023-2024
 */
#ifndef __SOMM23_EXCEPTION__
#define __SOMM23_EXCEPTION__

#include <exception>

#include "errno.h"

/** @{ */

/**
 * \brief The \b somm23 exception class
 * \ingroup exception
 */
class Exception: public std::exception
{
  public:
    int en;                 ///< (system) error number
    const char *func;       ///< name of function that has thrown the exception
    char msg[100];          ///< buffer to store the exception message

    /**
     * \brief the constructor
     * \param _en (system) error number 
     * \param _func name of function throwing the exception
     */
     Exception(int _en, const char *_func);

    /**
     * \brief default exception message
     * \return pointer to exception message
     */
    const char *what() const throw();
};

/** @} */

#endif /* __SOMM23_EXCEPTION__ */
