# iflog

C++ interface logging library. Easy to insert into if condition.

## Features

* C++11
* Header-only
* Easy to insert into statement.

## Examples

* if statement
  ```cpp
  if( foo.has_error() )
  if( IFLOG(foo.has_error()) )
  // LOG:main | foo.has_error() => true

  if( foo.get_result(&result) )
  if( IFLOG(foo.get_result(&result), result) )
  // LOG:main | foo.get_result(&result) => true , result => 1
  ```

* switch statement
  ```cpp
  switch( foo.get_status() )
  switch( IFLOG(foo.get_status()) )
  // LOG:main | foo.get_status() => 2
  ```

* while statement
  ```cpp
  while( !foo.is_completed() )
  while( IFLOG(!foo.is_completed()) )
  // LOG:main | !foo.is_completed() => false
  ```

* return statement
  ```cpp
  return foo.do_something(arg1, arg2);
  return IFLOG(foo.do_something(arg1, arg2), arg1, arg2);
  // LOG:main | foo.do_something(arg1, arg2) => -1 , arg1 => 0.3 , arg2 => 1.5
  ```

* void function
  ```cpp
  foo.void_function();
  IFLOG_VOID(foo.void_function(arg1, arg2));
  // LOG:main | foo.void_function() , arg1 => 0.3 , arg2 => 1.5
  ```

## License

  MIT License

## Compiler
* Visual C++ 2015 Update 3 or later
* gcc 6 or later
* clang 4 or later
