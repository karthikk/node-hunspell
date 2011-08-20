#include <v8.h>
#include <node.h>

#include "hunspell.hxx"

using namespace v8;
using namespace node;


static Hunspell *pSpell = new Hunspell("en_US.aff", "en_US.dic");

namespace spell_v8 {

	Handle<Value> IsValidWord(const Arguments &args) {
		HandleScope scope;
		v8::String::AsciiValue word(args[0]);
		int d = pSpell->spell(*word);
		return scope.Close(d > 0 ? True() : False());
	}

	Handle<Value> Suggest(const Arguments &args) {
		HandleScope scope;
		v8::String::AsciiValue word(args[0]);
		Local<Array> arr = Array::New();
		int d = pSpell->spell(*word);
		if (!d) {
			char **suggestions;
			int n = pSpell->suggest(&suggestions, *word);
			for (int i = 0; i < n; i++) {
				arr->Set(Integer::New(i), String::New(suggestions[i]));
			}
			pSpell->free_list(&suggestions, n);
		}
		return scope.Close(arr);
	}
}

extern "C"
void init(Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> t1 = FunctionTemplate::New(spell_v8::IsValidWord);
	Local<FunctionTemplate> t2 = FunctionTemplate::New(spell_v8::Suggest);

	target->Set(String::NewSymbol("isValidWord"), t1->GetFunction());
	target->Set(String::NewSymbol("suggest"), t2->GetFunction());
}
