#ifndef CONFIG_PARAMS_H
#define CONFIG_PARAMS_H
#include <string>
#include <vector>
#include <map>
#include "pugixml.hpp"
#include "OptionParser.h"
#include "ds_global.h"

class Config_params{
private:
    Config_params(){}
    static Config_params* instance;

    optparse::OptionParser parser_ = optparse::OptionParser() .description("Multilevel Machine Learning Library");

    optparse::Values options_;


    int main_function;

    //----- debug_export parameters -----
    int     debug_exp_CS;
    int     debug_exp_CS_level;
    int     debug_exp_MS;
    int     debug_exp_MS_level;
    int     debug_exp_MR;
    int     debug_exp_MR_level;


    std::string mlsvm_version;
    std::string mlclustering_version;
    std::string p_indices_f_name, p_dist_f_name;
    std::string n_indices_f_name, n_dist_f_name;
    std::string p_norm_data_f_name, n_norm_data_f_name;
    std::string test_ds_f_name, single_norm_data_f_name;
    std::string p_e_k_train_data_f_name, n_e_k_train_data_f_name;

    /// Descriptions are moved to param.xml
    //======= C++ parameters ========
    std::string cpp_srand_seed;
    int level;
    //======= main ========
    int         main_num_repeat_exp;
    int         main_num_kf_iter;
    int         main_current_exp_id;        //for export models
    int         main_current_kf_id;         //for export models
    int         main_current_level_id;      //for export models
    int         multi_level_status;
    std::string exp_info;

    //======= NN ========
    int         nn_number_of_classes;
    int         nn_number_of_neighbors;
    int         nn_distance_type;

    std::string nn_path;
    std::string nn_data_fname1;
    std::string nn_data_fname2;
    std::string nn_tmp_path;
    //======= Loader ========
    std::string ds_path;
    std::string ds_name;
    std::string tmp_path;
    int         pre_init_loader_matrix;
    bool        inverse_weight;
    int         ld_weight_type;
    double      ld_weight_param;
    //======= CS ========
    double      coarse_Eta;
    int         coarse_threshold;
    double      coarse_q ;
    int         coarse_r;
    int         cs_max_coarse_level;    // Control parameter to stop
    int         cs_use_real_points;
    double      cs_weak_edges_ft;       // filter threshold for weak edges
    bool        cs_boundary_points_status;  //0 means normal scenario, 1 means add boundary points
    double      cs_boundary_points_threshold;       // min entropy for a fine point to be considered as boundary point between 0 and 1
    int         cs_boundary_points_max_num;    // max number of fractions is going to add to each row of P matrix
    //======= Model selection ========
    int     ms_status;
    int     ms_limit;
    int     ms_svm_id;
    int     ms_first_stage;
    int     ms_second_stage;
    int     ms_best_selection;
//    double  ms_validation_part;
    double  ms_VD_sample_size_fraction;    // validation data
    int     ms_print_untouch_reuslts;
    double  ms_bs_gm_threshold;
    int     ms_save_final_model;
    //======= SVM ========
    int     svm_type;
    int     kernel_type;
    int     degree;
    double  gamma;
    double  coef0;
    double  nu;
    double  cache_size;
    double  C;
    double  eps;
    double  p;
    int     shrinking;
    int     probability;
    int     nr_weight;
    //========== Refinement ==========
    float   rf_add_fraction;
    bool    rf_add_distant_point_status;
    int     rf_weight_vol;
    std::vector<std::pair<int,int>> master_models_info;
    std::vector<int> levels_models_info;
    //========== Partitioning ==========
    int     pr_start_partitioning;
    int     pr_partition_max_size;
    int     pr_maj_voting_id;

//    std::vector<iter_summary> all_summary;
    std::vector<summary> all_summary;
    //======= Exp ========
    double best_C;
    double best_gamma;
    bool best_params_are_set;

    //======= Classificaiton Prediction ========
    int experiment_id;
    int kfold_id;

    // Methods
    void check_input_distance_parameters();
//    void check_input_prediction_parameters();

    void read_classification_training_parameters(pugi::xml_node& root,int argc, char * argv[]);
    void read_classification_prediction_parameters(pugi::xml_node& root,int argc, char * argv[]);
    void read_convert_files_parameters(pugi::xml_node& root,int argc, char * argv[]);
    void read_clustering_parameters(pugi::xml_node& root,int argc, char * argv[]);




public:
    enum program_parts {main, convert_files, zscore, flann, svm, prediction, clustring} ;
    static Config_params* getInstance();
    int  get_main_function() const { return main_function;  }

    void print_classification_training_params();
    void print_classification_prediction_params();
    void print_convert_files_params();
    void read_flann_parameters(pugi::xml_node& root,int argc, char * argv[]);
    void read_zscore_parameters(pugi::xml_node& root,int argc, char * argv[]);
    void print_flann_params();
    void print_zscore_params();

//    void set_inputs(std::string const ds_name, std::string const ds_version );
    void set_inputs_file_names();
    void set_file_names_for_save_flann();

    void set_ds_path(std::string const new_ds_path);
    void set_ds_name(std::string const new_ds_name);
    void debug_only_set_p_norm_data_path_file_name(std::string const path_file_name);
    void debug_only_set_n_norm_data_path_file_name(std::string const path_file_name);

    void init_to_default();
    void read_params(std::string XML_FILE_PATH,int argc, char * argv[], program_parts caller_func=main);


    void update_srand_seed();
    void debug_only_set_srand_seed(std::string new_seed);

    const std::string &get_ds_path()    const { return options_["ds_path"];}
    const std::string &get_ds_name()    const { return options_["ds_name"];}
    std::string get_tmp_path()   const ;
    const std::string &get_exp_info()   const { return options_["exp_info"];}

    const std::string &get_p_indices_f_name()           const {return p_indices_f_name;}
    const std::string &get_p_dist_f_name()              const {return p_dist_f_name;}
    const std::string &get_n_indices_f_name()           const {return n_indices_f_name;}
    const std::string &get_n_dist_f_name()              const {return n_dist_f_name;}
    const std::string &get_p_norm_data_f_name()         const {return p_norm_data_f_name;}
    const std::string &get_n_norm_data_f_name()         const {return n_norm_data_f_name;}
    const std::string &get_single_norm_data_f_name()    const {return single_norm_data_f_name;}
    const std::string &get_p_e_k_train_data_f_name()    const {return p_e_k_train_data_f_name;}
    const std::string &get_n_e_k_train_data_f_name()    const {return n_e_k_train_data_f_name;}

    void set_test_ds_f_name(std::string new_f_name) { test_ds_f_name = new_f_name;}
    void set_p_e_k_train_data_f_name(std::string new_f_name) { p_e_k_train_data_f_name = new_f_name;}
    void set_n_e_k_train_data_f_name(std::string new_f_name) { n_e_k_train_data_f_name = new_f_name;}
    std::string get_test_ds_f_name() const {return test_ds_f_name;}

    void add_final_summary(summary current_summary, int selected_level);
    int  get_best_level() const;  //in current k-fold

    void print_summary(const summary& summary_in, std::string caller_method, int level=-1, int iter=-1, int stage=-1, int fold=-1) const;
    void set_best_parameters(measures preferred_measure=Gmean);
    bool get_best_params_status() const{ return this->best_params_are_set; }
    double get_best_C() const{ return this->best_C; }
    double get_best_gamma() const{ return this->best_gamma; }
    void print_final_results() const;
    void print_ref_result(const std::vector<ref_results>& v_ref_results) const;

    // Debug parameters
    int get_debug_exp_CS()          const { return debug_exp_CS; }
    int get_debug_exp_CS_level()    const { return debug_exp_CS_level; }
    int get_debug_exp_MS()          const { return debug_exp_MS; }
    int get_debug_exp_MS_level()    const { return debug_exp_MS_level; }
    int get_debug_exp_MR()          const { return debug_exp_MR; }
    int get_debug_exp_MR_level()    const { return debug_exp_MR_level; }
    // NN
    int   get_nn_number_of_classes()    const { return stoi(options_["nn_number_of_classes"]);}
    int   get_nn_number_of_neighbors()  const { return stoi(options_["nn_number_of_neighbors"]);}
    int   get_nn_distance_type()        const { return stoi(options_["nn_distance_type"]);}
    std::string get_nn_path()           const { return options_["nn_path"];}
    std::string get_nn_data_fname1()    const { return options_["nn_data_fname1"];}
    std::string get_nn_data_fname2()    const { return options_["nn_data_fname2"];}
    std::string get_nn_tmp_path()       const { return options_["nn_tmp_path"];}
    // Main
    std::string get_cpp_srand_seed()        const { return options_["cpp_srand_seed"];}
    int    get_main_num_repeat_exp()        const { return stoi(options_["main_num_repeat_exp"]);}
    int    get_main_num_kf_iter()           const { return stoi(options_["main_num_kf_iter"]);}
    int    get_multi_level_status()         const { return stoi(options_["multi_level_status"]); }    
    int    get_main_current_exp_id()        const {return main_current_exp_id;}        //for export models
    int    get_main_current_kf_id()         const {return main_current_kf_id;}         //for export models
    int    get_main_current_level_id()      const {return main_current_level_id;}      //for export models
    int    set_main_current_exp_id(int new_id)        { main_current_exp_id = new_id;}        //for export models
    int    set_main_current_kf_id(int new_id)         { main_current_kf_id = new_id;}         //for export models
    int    set_main_current_level_id(int new_id)      { main_current_level_id = new_id;}      //for export models

    // Loader
    bool   get_inverse_weight()     const { return inverse_weight; }
    int    get_ld_weight_type()     const { return ld_weight_type; }
    double get_ld_weight_param()    const { return ld_weight_param; }
    int    get_pre_init_loader_matrix() const{ return stoi(options_["pre_init_loader_matrix"]);}

    // Coarsening
    double  get_coarse_Eta() const          { return stod(options_["coarse_Eta"]); }
    double  get_coarse_threshold() const    { return stod(options_["coarse_threshold"]); }
    double  get_coarse_q() const            { return stod(options_["coarse_q"]); }
    int     get_coarse_r() const            { return stoi(options_["coarse_r"]); }
    int     get_cs_max_coarse_level() const { return stoi(options_["cs_max_coarse_level"]); }
    int     get_cs_use_real_points()  const { return cs_use_real_points; }
    double  get_cs_weak_edges_ft()    const { return stod(options_["cs_weak_edges_ft"]); }
    bool    get_cs_boundary_points_status()     const { return (bool) stoi(options_["cs_boundary_points_status"]); }
    double  get_cs_boundary_points_threshold()  const { return stod(options_["cs_boundary_points_threshold"]); }
    int     get_cs_boundary_points_max_num()    const { return stoi(options_["cs_boundary_points_max_num"]); }

    // Model Selection
    int     get_ms_status() const         { return  stoi(options_["ms_status"]); }
    int     get_ms_limit() const          { return  stoi(options_["ms_limit"]);}
    int     get_ms_svm_id() const         { return  stoi(options_["ms_svm_id"]); }
    int     get_ms_first_stage() const    { return  stoi(options_["ms_first_stage"]); }
    int     get_ms_second_stage() const   { return  stoi(options_["ms_second_stage"]); }
    float   get_ms_VD_sample_size_fraction()    const { return stof(options_["ms_VD_sample_size_fraction"]);}
    int     get_ms_print_untouch_reuslts()      const { return  stoi(options_["ms_print_untouch_reuslts"]); }
    int     get_ms_save_final_model()           const { return ms_save_final_model; }

    double  get_ms_bs_gm_threshold()    const { return ms_bs_gm_threshold; }
    int     get_ms_best_selection()     const { return stoi(options_["ms_best_selection"]); }

    // SVM
    int     get_svm_svm_type()      const { return svm_type; }
    int     get_svm_kernel_type()   const { return stoi(options_["kernel_type"]); }
    int     get_svm_degree()        const { return degree; }
    double  get_svm_gamma()         const { return stod(options_["gamma"]); }
    double  get_svm_coef0()         const { return coef0; }
    double  get_svm_nu()            const { return nu; }
    double  get_svm_cache_size()    const { return cache_size; }
    double  get_svm_p()             const { return p; }
    int     get_svm_nr_weight()     const { return nr_weight; }
    double  get_svm_C()             const { return  stod(options_["C"]); }
    double  get_svm_eps()           const { return  stod(options_["eps"]); }
    int     get_svm_shrinking()     const { return  stoi(options_["shrinking"]); }
    int     get_svm_probability()   const { return  stoi(options_["probability"]); }

    // Refienment
    bool    get_rf_add_distant_point_status()   const { return (bool) stoi(options_["rf_add_distant_point_status"]); }
    float   get_rf_add_fraction()               const { return  stof(options_["rf_add_fraction"]); }
    int     get_rf_weight_vol()                 const { return  stoi(options_["rf_weight_vol"]); }
    void    set_master_models_info();
    void    set_levels_models_info();
//    void    check_models_metadata();        //for debug
    void    update_levels_models_info(int level_id, int num_models);
    void    update_master_models_info();
    void    export_models_metadata();

    // Partioning
    int     get_pr_maj_voting_id() const         { return  stoi(options_["pr_maj_voting_id"]); }
    int     get_pr_start_partitioning()         const { return  stoi(options_["pr_start_partitioning"]); }
    int     get_pr_partition_max_size()         const { return  stoi(options_["pr_partition_max_size"]); }

    // - - - - - Classification prediction  - - - - -
    int    get_experiment_id()      const { return stoi(options_["experiment_id"]);}
    int    get_kfold_id()           const { return stoi(options_["kfold_id"]);}
};

#endif // CONFIG_PARAMS_H


