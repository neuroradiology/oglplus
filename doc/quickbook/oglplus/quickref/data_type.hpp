/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_data_type_utils
namespace oglplus {

template <typename T>
struct IsGLDataType /*<
Indicates if the the T is a GL data type.
>*/
 : std::integral_constant<bool, ...>
{ };

template <typename T>
struct DataTypeCT /*<
Returns a compile-time constant value from the __DataType
enumeration for the specified type [^T]. This meta-function
is defined only for types for which [^IsGLDataType] returns [^std::true_type].
>*/
 : std::integral_constant<__DataType, ...>
{ };

template <typename T>
__DataType GetDataType(void); /*<
Returns a value from the __DataType enueration for the specified type [^T].
>*/

} // namespace oglplus
//]

