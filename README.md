# str
A simple string library. Has some cool features such as xor operations and more! This library will work for any C++ version.

```cpp
#include "str.hpp"
#include <iostream>

namespace str_example
{
    void convert( )
    {
        printf( "--- CONVERT EXAMPLE BEGIN ---\n\n" );

        auto s = str( "convert example" );
        void* pointer = reinterpret_cast< void* >( s.get( ) );

        printf( "pointer: %p | conversion: %s\n", pointer, s.convert<char*>( pointer ) );
       
        for ( int i = 0; i < s.len( ); i++ )
            printf( "0x%llx ", reinterpret_cast<unsigned char*>(pointer)[i] );

        printf( "\n\n--- CONVERT EXAMPLE END ---\n\n" );
    }

    void bytes( )
    {
        printf( "--- BYTES EXAMPLE BEGIN ---\n\n" );

        auto s = str( "bytes example" );
        for ( int i = 0; i < s.len( ); i++ )
            printf( "0x%llx ", s.bytes()[i] );

        printf( "\n\n--- BYTES EXAMPLE END ---\n\n" );
    }

    void xor_ ( )
    {
        printf( "--- XOR EXAMPLE BEGIN ---\n\n" );

        auto s = str( "my message" );

        auto key = ( char* )"secret_key";
        auto enc = s.xor_encrypt( s.get(), key );
        auto dec = s.xor_encrypt( enc, key );

        printf( "xor_encrypted: %s\n", enc );
        printf( "xor_decrypted: %s\n", dec );

        printf( "\n--- XOR EXAMPLE END ---\n\n" );
    }
}

int main()
{
    str_example::convert( );
    str_example::bytes( );
    str_example::xor_( );

    std::cin.get( );
}
```
