/*-
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may do so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: soc2013/dpl/head/sys/dev/isci/scil/sci_base_iterator.h 231418 2012-02-07 17:43:58Z jimharris $
 */
/**
 * @file
 *
 * @brief This file contains the protected interface to the iterator class.
 *        Methods Provided:
 *        - sci_base_iterator_construct()
 */

#ifndef _SCI_BASE_ITERATOR_H_
#define _SCI_BASE_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//******************************************************************************
//*
//*     I N C L U D E S
//*
//******************************************************************************

#include <dev/isci/scil/sci_iterator.h>
#include <dev/isci/scil/sci_abstract_list.h>

//******************************************************************************
//*
//*     C O N S T A N T S
//*
//******************************************************************************

//******************************************************************************
//*
//*     T Y P E S
//*
//******************************************************************************

/**
 * @struct SCI_BASE_ITERATOR
 *
 * @brief This object represents an iterator of an abstract list.
 *
 */
typedef struct SCI_BASE_ITERATOR
{
   /**
    * This field points to the list iterated by this iterator.
    */
   SCI_ABSTRACT_LIST_T * list;

   /**
    * This field points to the list element currently referenced by this
    *  iterator.
    */
   SCI_ABSTRACT_ELEMENT_T * current;

} SCI_BASE_ITERATOR_T;

//******************************************************************************
//*
//*     P U B L I C       M E T H O D S
//*
//******************************************************************************

#if !defined(DISABLE_SCI_ITERATORS)

void sci_base_iterator_construct(
   SCI_ITERATOR_HANDLE_T   iterator,
   SCI_ABSTRACT_LIST_T   * list
);

#else // !defined(DISABLE_SCI_ITERATORS)

#define sci_base_iterator_construct(the_iterator, the_list)

#endif // !defined(DISABLE_SCI_ITERATORS)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _BASE_ITERATOR_H_
