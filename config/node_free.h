#pragma once

#define MORPH(name, k1, modifiers, k2) \
/ { \
  behaviors { \
    name: name { \
      compatible = "zmk,behavior-mod-morph"; \
      #binding-cells = <0>; \
      bindings = <k1>, <k2>; \
      mods = <(modifiers)>; \
    }; \
  }; \
};

#define TAPDANCE(name, ...) \
/ { \
  behaviors { \
    name: name {  \
      compatible = "zmk,behavior-tap-dance"; \
      #binding-cells = <0>; \
      bindings = __VA_ARGS__; \
    }; \
  }; \
};

#define MORPH_UP(name, k1, k2) MORPH(name, k1, MOD_LSFT|MOD_RSFT, k2)

#define MACRO(...) \
/ { \
  macros { \
    ZMK_MACRO(__VA_ARGS__) \
  }; \
};

#define COND_LAYER(if_layers, then_layer) \
/ { \
  conditional_layers { \
    compatible = "zmk,conditional-layers"; \
    then_layer##_cond_layer { \
      if-layers = <if_layers>; \
      then-layer = <then_layer>; \
    }; \
  }; \
};

#define LAYER(id, display_name, layout) \
/ { \
  keymap { \
    compatible = "zmk,keymap"; \
    id##_layer { \
      label = display_name; \
      bindings = <layout>; \
    }; \
  }; \
};

// Homerow mods macro
// - NOTE: Updated here from tap-prefered to balanced
/ {
  behaviors {
    hm_l: hm_l {
      compatible = "zmk,behavior-hold-tap";
      #binding-cells = <2>;
      flavor = "balanced";
      tapping-term-ms = <175>;
      quick-tap-ms = <175>;
      require-prior-idle-ms = <150>;
      hold-trigger-on-release;
      hold-trigger-key-positions = <6 7 8 9 10 11 18 19 20 21 22 23 30 31 32 33 34 35 39 40 41>;
      bindings = <&kp>, <&kp>;
    };
    hm_r: hm_r {
      compatible = "zmk,behavior-hold-tap";
      #binding-cells = <2>;
      flavor = "balanced";
      tapping-term-ms = <175>;
      quick-tap-ms = <175>;
      require-prior-idle-ms = <150>;
      hold-trigger-on-release;
      hold-trigger-key-positions = <0 1 2 3 4 5 12 13 14 15 16 17 24 25 26 27 28 29 36 37 38>;
      bindings = <&kp>, <&kp>;
    };
  };
};

