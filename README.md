# iflog

C++ interface logging library. Easy to insert into if condition.

## Features

* C++11
* Header-only
* Easy to insert into statement.

## Examples

* if statement

    * before
    `if( foo.has_error() )`

    * after
    `if( IFLOG(foo.has_error()) )`

    * output
    `LOG:main | foo.has_error() => true`

    * before
    `if( foo.get_result(&result) )`

    * after
    `if( IFLOG(foo.get_result(&result), result) )`

    * output
    `LOG:main | foo.get_result(&result) => true , result => 1`

* switch statement

    * before
    `switch( foo.get_status() )`

    * after
    `switch( IFLOG(foo.get_status()) )`

    * output
    `LOG:main | foo.get_status() => 2`

* while statement

    * before
    `while( !foo.is_completed() )`

    * after
    `while( IFLOG(!foo.is_completed()) )`

    * output
    `LOG:main | !foo.is_completed() => false`

* return statement

    * before
    `return foo.do_something(arg1, arg2);`

    * after
    `return IFLOG(foo.do_something(arg1, arg2), arg1, arg2);`

    * output
    `LOG:main | foo.do_something(arg1, arg2) => -1 , arg1 => 0.3 , arg2 => 1.5`

* void function

    * before
    `foo.void_function();`

    * after
    `IFLOG_VOID(foo.void_function(arg1, arg2));`

    * output
    `LOG:main | foo.void_function() , arg1 => 0.3 , arg2 => 1.5`

## License

  MIT License

## Compiler
* Visual C++ 2015 Update 3 or later
* gcc 6 or later
* clang 4 or later
