#include "std.h"
#include "lpc_incl.h"

Program globalProgram;

int total_num_prog_blocks, total_prog_block_size;



void program_s::reference(const char * from)
{
    ref++;
    debug(d_flag, ("reference_prog: /%s ref %d (%s)\n",
               filename, ref, from));
}

// this is destructor? 
void program_s::deallocate()
{
    int i;

    debug(d_flag, ("free_prog: /%s\n", filename));
    
    total_prog_block_size -= total_size;
    total_num_prog_blocks -= 1;

    /* Free all function names. */
    for (i = 0; i < num_functions_defined; i++)
        if (function_table[i].funcname)
            free_string(function_table[i].funcname);
    /* Free all strings */
    for (i = 0; i < num_strings; i++)
        free_string(strings[i]);
    /* Free all variable names */
    for (i = 0; i < num_variables_defined; i++)
        free_string(variable_table[i]);
    /* Free all inherited objects */
    for (i = 0; i < num_inherited; i++){
    	program_t *tmp = inherit[i].prog;
    	globalProgram.free_prog(&tmp); //don't want to mess up the prog pointer in the inherited ob
    }
    free_string(filename);

    /*
     * We're going away for good, not just being swapped, so free up
     * line_number stuff.
     */
    if (file_info)
        FREE(file_info);
    
    // FREE((char *) progp);
}

/*
 * Decrement reference count for a program. If it is 0, then free the prgram.
 * The flag free_sub_strings tells if the propgram plus all used strings
 * should be freed. They normally are, except when objects are swapped,
 * as we want to be able to read the program in again from the swap area.
 * That means that strings are not swapped.
 */
void Program::free_prog (program_t **progp)
{
    (*progp)->ref--;
    if ((*progp)->ref > 0) {
      *progp = (program_t *)2;//NULL;
        return;
    }
    if ((*progp)->func_ref > 0) {
      *progp = (program_t *)3;//NULL;
        return;
    }

    (*progp)->deallocate();
    FREE( (char*)*progp );
    *progp = (program_t *)4;//NULL;
}

char *program_s::variable_name (int idx) {
    int i = num_inherited - 1;
    int first;

    if (i > -1)
        first = inherit[i].variable_index_offset + inherit[i].prog->num_variables_total;
    else
        return variable_table[idx];
    if (idx >= first)
        return variable_table[idx - first];
    while (idx < inherit[i].variable_index_offset)
        i--;
    return (inherit[i].prog)->variable_name(idx - inherit[i].variable_index_offset);
}

function_t *program_s::find_func_entry (int index) {
    register int low, mid, high;
    

    /* Walk up the inheritance tree to the real definition */   
    if (function_flags[index] & FUNC_ALIAS) {
        index = function_flags[index] & ~FUNC_ALIAS;
    }
    
    program_s* prog = this;
    while (prog->function_flags[index] & FUNC_INHERITED) {
        low = 0;
        high = num_inherited -1;
        
        while (high > low) {
            mid = (low + high + 1) >> 1;
            if (prog->inherit[mid].function_index_offset > index)
                high = mid -1;
            else low = mid;
        }
        index -= prog->inherit[low].function_index_offset;
        prog = prog->inherit[low].prog;
    }
    
    index -= prog->last_inherited;

    return prog->function_table + index;
}

