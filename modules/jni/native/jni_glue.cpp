
#include "jni_glue.h"

namespace bbJNI{

	jvalue *makeArgs( JNIEnv *env,bbArray<bbVariant> args ){
	
		jvalue *jargs=new jvalue[args.length()];
		
		memset( jargs,0,sizeof( jvalue ) * args.length() );
		
		jvalue *jarg=jargs;
		
		for( int i=0;i<args.length();++i ){
		
			bbVariant arg=args[i];
			
			bbTypeInfo *type=arg.getType();
			
			if( type==bbGetType<bbInt>() ){
			
				bbInt val=arg.get<bbInt>();
				
				jarg->i=val;
			
			}else if( type==bbGetType<bbString>() ){
			
				bbString str=arg.get<bbString>();
				
				int n=str.utf8Length()+1;
				
				char *buf=new char[n];
				
				str.toCString( buf,n );
				
				jstring jstr=env->NewStringUTF( buf );
				
				jarg->l=jstr;
			
			}else{
			
				bbRuntimeError( "Can't evaluate JNI method param of typ:"+type->toString() );
			}
			
			++jarg;
		}
		
		return jargs;
	}
	
	void CallVoidMethod( JNIEnv *env,jobject obj,jmethodID methodID,bbArray<bbVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		env->CallVoidMethodA( obj,methodID,jargs );
		
		delete[] jargs;
	}

}

